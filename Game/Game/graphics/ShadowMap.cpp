#include "stdafx.h"
#include "ShadowMap.h"

ShadowMap::ShadowMap()
{
}


ShadowMap::~ShadowMap()
{
}

void ShadowMap::Init()
{
	m_shadowMapRT.Create(
		2048,
		2048,
		DXGI_FORMAT_R32_FLOAT
	); 
	m_width = 3000.0f;
	m_height = 3000.0f;
	InitConstantBuffer();
}

void ShadowMap::UpdateFromLightDirection(CVector3 lightCameraPos, CVector3 lightDir)
{
	//ライトの方向によって、ライトカメラの上方向を決める。
	CVector3 lightCameraUpAxis;
	if (fabsf(lightDir.y) > 0.99998f) {
		//ほぼ真上or真下を向いているので、1,0,0を上方向とする。
		lightCameraUpAxis = CVector3::AxisX();
	}
	else {
		//真上を向いていないときは、0,1,0を上方向とする。
		lightCameraUpAxis = CVector3::AxisY();
	}
	//カメラの上方向が決まったので、ライトビュー行列を計算する。
	m_lightViewMatrix.MakeLookAt(
		m_lightCameraPosition,
		m_lightCameraTarget,
		lightCameraUpAxis
	);

	//ライトプロジェクション行列を作成する。
	//太陽光からの影を落としたいなら、平行投影行列を作成する。
	m_lightProjMatrix.MakeOrthoProjectionMatrix(
		m_width,
		m_height,
		0.1f,
		5000.0f
	);
}
void ShadowMap::UpdateFromLightTarget(CVector3 lightCameraPos, CVector3 lightCameraTarget)
{
	//デバック
	m_lightCameraTarget = lightCameraTarget;
	m_lightCameraPosition = lightCameraPos;
	//ライトの方向を計算する。
	auto lightDir = m_lightCameraTarget - m_lightCameraPosition;
	if (lightDir.Length() < 0.0001f) {
		//ライトカメラの注視点と視点が近すぎる。
		//恐らくバグなので、クラッシュさせる。
		std::abort();
	}
	//正規化して、方向ベクトルに変換する。
	lightDir.Normalize();
	//
	UpdateFromLightDirection(lightCameraPos, lightDir);
}

void ShadowMap::RenderToShadowMap()
{
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//レンダリングターゲットを切り替える。
	ID3D11RenderTargetView* rts[] = {
		m_shadowMapRT.GetRenderTargetView()
	};
	d3dDeviceContext->OMSetRenderTargets(1, rts, m_shadowMapRT.GetDepthStensilView());
	//ビューポートを設定。
	d3dDeviceContext->RSSetViewports(1, m_shadowMapRT.GetViewport());
	//シャドウマップをクリア。
	//一番奥のZは1.0なので、1.0で塗りつぶす。
	float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; //red,green,blue,alpha
	m_shadowMapRT.ClearRenderTarget(clearColor);
	m_ligCamParam.mLightProj = m_lightProjMatrix;
	m_ligCamParam.mLightView = m_lightViewMatrix;
	d3dDeviceContext->UpdateSubresource(m_shadowMapCB, 0, nullptr, &m_ligCamParam, 0, 0);

	d3dDeviceContext->VSSetConstantBuffers(1, 1, &m_shadowMapCB);
	d3dDeviceContext->PSSetConstantBuffers(1, 1, &m_shadowMapCB);
	//シャドウキャスターをシャドウマップにレンダリング。
	for (auto& caster : m_shadowCasters) {
		caster->Draw(
			enRenderMode_CreateShadowMap,
			m_lightViewMatrix,
			m_lightProjMatrix
		);
	}
	//キャスターをクリア。
	m_shadowCasters.clear();
}

void ShadowMap::InitConstantBuffer()
{
	//作成するバッファのサイズをsizeof演算子で求める。
	int bufferSize = sizeof(SLightCameraParam);
	//どんなバッファを作成するのかをせてbufferDescに設定する。
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));				//０でクリア。
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;						//バッファで想定されている、読み込みおよび書き込み方法。
	bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;	//バッファは16バイトアライメントになっている必要がある。
																//アライメントって→バッファのサイズが16の倍数ということです。
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//バッファをどのようなパイプラインにバインドするかを指定する。
																//定数バッファにバインドするので、D3D11_BIND_CONSTANT_BUFFERを指定する。
	bufferDesc.CPUAccessFlags = 0;								//CPU アクセスのフラグです。
																//CPUアクセスが不要な場合は0。
	//続いて、ライト用の定数バッファを作成。		//SDirectionLightは16byteの倍数になっているので、切り上げはやらない。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_shadowMapCB);
}
