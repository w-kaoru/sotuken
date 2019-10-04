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
	m_testes.Init(0.1f, 0.1f, m_position);
	return true;
}

void Bullet::Update()
{
	if (m_testes.Gethit() == true)
	{
		HitFlag = true;
	}
	m_position += m_moveSpeed;
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
	m_testes.Execute(1.0f / 30.0f, m_position);
}

void Bullet::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}