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
	m_testes.Init(10.0f, m_position);
	m_testes.GetRigidBody()->GetBody()->setUserIndex(enCollisionAttr_PlayerBullet);
	m_enemy = FindGO<TestEnemy>("TestEnemy");
	return true;
}
void Bullet::BulletMove()
{
	m_position = m_testes.Execute(1.0f / 30.0f, m_moveSpeed);
	
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
}
void Bullet::Update()
{
	//CVector3 v = m_position - m_enemy->GetPosition();
	//float len = v.Length();
	//if (len <= 90.0f)
	//{
	//	HitFlag = true;
	//}

	BulletMove();
	if (m_testes.GetE_bullethit() == true) {
		HitFlag = true;
	}
}

void Bullet::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}