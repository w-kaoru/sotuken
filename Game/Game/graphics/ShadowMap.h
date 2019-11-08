#pragma once
#include "RenderTarget.h"
#include "SkinModel.h"
class ShadowMap :public NoncCopyable
{
public:
	ShadowMap();
	~ShadowMap();

	// ライトビュー行列を取得。
	CMatrix GetLighViewMatrix() const
	{
		return m_lightViewMatrix;
	}

	// ライトプロジェクション行列を取得。
	CMatrix GetLightProjMatrix() const
	{
		return m_lightProjMatrix;
	}
	//初期化。
	void Init();
	void UpdateFromLightTarget(CVector3 lightCameraPos, CVector3 lightCameraTarget);
	void UpdateFromLightDirection(CVector3 lightCameraPos, CVector3 lightDir);
	void RenderToShadowMap();

	// シャドウキャスターを登録。
	// この関数を使って、登録されたキャスターが
	// シャドウマップに描画されます。
	// 登録されたキャスターのリストはRenderToShadowMapを呼び出したら
	// クリアされるため、常に影を生成したい場合は、
	// 毎フレームこの関数を呼び出す必要があります。
	void RegistShadowCaster(SkinModel* shadowCaster)
	{
		m_shadowCasters.push_back(shadowCaster);
	}
	// シャドウキャスターをリストから除外する。
	void UnregistShadowCaster(SkinModel* shadowCaster)
	{
		//shadowCasterのインスタンスをリストから検索する。
		auto it = std::find(
			m_shadowCasters.begin(),
			m_shadowCasters.end(),
			shadowCaster
		);
		if (it != m_shadowCasters.end()) {
			//見つかったのでコンテナから除外する。
			m_shadowCasters.erase(it);
		}
	}
	// シャドウマップのSRVを取得。
	// <returns>シャドウマップのSRV</returns>
	ID3D11ShaderResourceView* GetShadowMapSRV()
	{
		return m_shadowMapRT.GetRenderTargetSRV();
	}
private:
	CVector3 m_lightCameraPosition = CVector3::Zero();	//ライトカメラの視点。
	CVector3 m_lightCameraTarget = CVector3::Zero();	//ライトカメラの注視点。
	CMatrix m_lightViewMatrix = CMatrix::Identity();	//ライトビュー行列。
	CMatrix m_lightProjMatrix = CMatrix::Identity();	//ライトプロジェクション行列。
	RenderTarget m_shadowMapRT;							//シャドウマップを描画するレンダリングターゲット。
	std::vector<SkinModel*> m_shadowCasters;			//シャドウキャスターの配列。
};