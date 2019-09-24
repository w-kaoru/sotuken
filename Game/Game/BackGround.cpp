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
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/TestGround.cmo");
	m_staticObject.CreateMeshObject(m_model, m_pos, m_rot);
	return true;
}

void BackGround::Update()
{
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
}

void BackGround::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}