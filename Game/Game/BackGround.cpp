#include "stdafx.h"
#include "BackGround.h"
#include "GameCamera.h"


BackGround::BackGround()
{	
}

BackGround::~BackGround()
{
}

bool BackGround::Start()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/CityMap1.cmo");
	m_staticObject.CreateMeshObject(m_model, m_pos, m_rot);
	m_model.SetShadowReciever(true);
	return true;
}

void BackGround::Update()
{
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);
}

void BackGround::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void BackGround::Draw(int player_num)
{
	m_model.Draw(
		enRenderMode_Normal,
		g_gameCamera3D[player_num]->GetCamera().GetViewMatrix(),
		g_gameCamera3D[player_num]->GetCamera().GetProjectionMatrix()
	);
}