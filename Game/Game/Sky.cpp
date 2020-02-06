#include "stdafx.h"
#include "Sky.h"
#include "GameCamera.h"

//todo 空マップ。
ID3D11ShaderResourceView* g_skyMapSRV = nullptr;
Sky::Sky()
{
}


Sky::~Sky()
{
}

bool Sky::Start()
{

	m_skymodel.Init(L"Assets/modelData/sky.cmo");

	//todo 空マップをロード。
	//ファイル名を使って、テクスチャをロードして、ShaderResrouceViewを作成する。
	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/skyCubeMap.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &g_skyMapSRV);
	m_skymodel.SetskyMap(g_skyMapSRV);
	return true;
}

void Sky::Update()
{
	m_skymodel.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3{ 10000.0f, 10000.0f, 10000.0f });
}

void Sky::Draw()
{
	m_skymodel.Draw(
		enRenderMode_CubeMap,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Sky::Draw(int player_num)
{
	m_skymodel.Draw(
		enRenderMode_CubeMap,
		g_gameCamera3D[player_num]->GetCamera().GetViewMatrix(),
		g_gameCamera3D[player_num]->GetCamera().GetProjectionMatrix()
	);
}