#include "stdafx.h"
#include "Bullet.h"
#include "TestEnemy.h"
#include "Physics/CollisionAttr.h"
#include "GameCamera.h"

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
	if (m_bulletCon) delete m_bulletCon;
}

bool Bullet::Start()
{	
	m_explosionse = NewGO<prefab::CSoundSource>(0);
	m_attsckse = NewGO<prefab::CSoundSource>(0);
	m_explosionse->Init(L"Assets/sound/explosion.wav", true);
	m_explosionse->SetVolume(0.5f);
	m_attsckse->Init(L"Assets/sound/battery1.wav", true);
	m_attsckse->Play(false);
	m_model.Init(L"Assets/modelData/bullet1.cmo");
	m_bulletCon->SetPosition(m_position);
	//向きを変える。
	auto angle = atan2f(g_gameCamera3D[m_number]->GetForward().x, g_gameCamera3D[m_number]->GetForward().z);
	m_rotation.SetRotation(CVector3::AxisY(), angle);
	
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
	
	m_model.UpdateWorldMatrix(m_position,m_rotation, CVector3::One());
}

void Bullet::Update()
{
	m_bulletDeleteTime++;
	BulletMove();
	if (m_bulletCon->GetBulletHit() == true) {
		m_explosionse->Play(false);
		m_hitpos = m_bulletCon->GetHitPos();
		m_hitFlag = true;
	}
	if (m_bulletCon->Gethit() == true)
	{
		m_explosionse->Play(false);
		m_hitpos = m_bulletCon->GetHitPos();
		IsHit = true;
	}
	m_number = m_bulletCon->GetNumber();
	m_hitNumber = m_bulletCon->GetHitNumber();
}

void Bullet::Draw()
{
	/*m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);*/
}

void Bullet::Draw(int player_num)
{
	m_model.Draw(
		enRenderMode_Normal,
		g_gameCamera3D[player_num]->GetCamera().GetViewMatrix(),
		g_gameCamera3D[player_num]->GetCamera().GetProjectionMatrix()
	);
}