#include "stdafx.h"
#include "TestEnemy.h"
#include "Physics/CollisionAttr.h"
#include "Bullet/Bullet.h"
#include "Bullet/BulletManeger.h"
#include "Define.h"


TestEnemy::TestEnemy()
{
}


TestEnemy::~TestEnemy()
{
}

bool TestEnemy::Start()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_pos.x = 50.0f;
	m_pos.z = -500.0f;
	m_bullet = FindGO<Bullet>("Bullet");
	m_charaCon.Init(50.0f, 50.0f, m_pos);
	m_charaCon.GetRigidBody()->GetBody()->setUserIndex(enCollisionAttr_Enemy);
	//m_bullet->GetBulletController()->GetRigidBody()->GetBody()->setUserIndex(enCollisionAttr_Enemy);
	return true;
}

void TestEnemy::FireBullets(float speed)
{
	m_bulletmaneger = NewGO<BulletManeger>(1, "BulletManeger");
	Bullet* bullet = m_bulletmaneger->NewBullet();
	bullet->SetMoveSpeed(m_forward * speed);
	CVector3 pos = m_pos;
	pos.y += 50.0f;
	bullet->SetPosition(pos);
}

void TestEnemy::Move()
{
	m_moveSpeed.y += -1800.0f * m_deltatime;
}

void TestEnemy::Update()
{
	CMatrix rotMatrix;
	rotMatrix.MakeRotationFromQuaternion(m_rot);
	m_forward.x = rotMatrix.m[2][0];
	m_forward.y = rotMatrix.m[2][1];
	m_forward.z = rotMatrix.m[2][2];
	m_forward.Normalize();
	m_pos = m_charaCon.Execute(1.0f / 30.0f, m_moveSpeed);
	//FireBullets(10.0f);

	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);
}

void TestEnemy::Turn()
{
	//向きを変える。
	if (fabsf(m_moveSpeed.x) > 0.1f
		|| fabsf(m_moveSpeed.z) > 0.1f) {
		auto angle = atan2f(m_moveSpeed.x, m_moveSpeed.z);
		m_rot.SetRotation(CVector3::AxisY(), angle);
	}
}

void TestEnemy::Draw()
{

	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}