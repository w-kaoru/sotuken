#include "stdafx.h"
#include "BackGround.h"


BackGround::BackGround()
{	
}

BackGround::~BackGround()
{
}

bool BackGround::Start()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/Showcase_desert.cmo");
	m_staticObject.CreateMeshObject(m_model, m_pos, m_rot);
	m_model.SetShadowReciever(true);
	return true;
}

void BackGround::Update()
{
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
}

void BackGround::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}