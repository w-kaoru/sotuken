#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

bool Bullet::Start()
{
	m_model.Init(L"Assets/modelData/bullet.cmo");

	return true;
}

void Bullet::Update()
{
	m_position += m_moveSpeed;
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
}

void Bullet::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}