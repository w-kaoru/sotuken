#include "stdafx.h"
#include "Bullet.h"
#include "TestEnemy.h"
#include "Physics/CollisionAttr.h"

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
	if (m_bulletCon) delete m_bulletCon;
}

bool Bullet::Start()
{	
	m_model.Init(L"Assets/modelData/bullet1.cmo");
	m_bulletCon->SetPosition(m_position);
	return true;
}
void Bullet::Init(int collision, int number)
{
	m_bulletCon = new BulletController;
	m_bulletCon->Init(10.0f, m_position);
	m_bulletCon->GetRigidBody()->GetBody()->setUserIndex((EnCollisionAttr)collision);
	m_bulletCon->SetHitNumber(number);
}
void Bullet::BulletMove()
{
	m_position = m_bulletCon->Execute(1.0f / 30.0f, m_moveSpeed);
	
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
}
void Bullet::Update()
{
	m_bulletDeleteTime++;
	BulletMove();
	if (m_bulletCon->GetBulletHit() == true) {
		m_hitFlag = true;
	}
	if (m_bulletCon->Gethit() == true)
	{
		IsHit = true;
	}
	m_number = m_bulletCon->GetNumber();
}

void Bullet::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}