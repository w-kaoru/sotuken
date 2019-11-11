#include "stdafx.h"
#include "Bullet.h"
#include "TestEnemy.h"
#include "Physics/CollisionAttr.h"

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

bool Bullet::Start()
{
	m_model.Init(L"Assets/modelData/bullet.cmo");
	m_bulletCon.Init(10.0f, m_position);
	m_bulletCon.GetRigidBody()->GetBody()->setUserIndex(enCollisionAttr_PlayerBullet);
	m_enemy = FindGO<TestEnemy>("TestEnemy");
	return true;
}
void Bullet::BulletMove()
{
	m_position = m_bulletCon.Execute(1.0f / 30.0f, m_moveSpeed);
	
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
}
void Bullet::Update()
{

	BulletMove();
	if (m_bulletCon.GetE_bullethit() == true) {
		E_HitFlag = true;
	}
	if (m_bulletCon.GetP_bullethit() == true)
	{
		P_HitFlag = true;
		m_bulletCon.RemoveRigidBoby();
	}
}

void Bullet::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}