#include "stdafx.h"
#include "TestEnemy.h"
#include "Physics/CollisionAttr.h"
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
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_enemyhp.Init(L"Assets/sprite/hp_gauge.dds", 40.0f, 10.0f);
	m_pos.x = 50.0f;
	m_pos.z = -500.0f;
	m_charaCon.Init(20.0f, 50.0f, m_pos);
	m_charaCon.GetRigidBody()->GetBody()->setUserIndex(enCollisionAttr_Enemy);
	m_bulletmaneger = FindGO<BulletManeger>("BulletManeger");
	return true;
}

void TestEnemy::FireBullets(float speed)
{
	
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

void TestEnemy::HPGage()
{
	//�|�W�V�����𓪂̏�t�߂ɂ���B
	auto pos = m_pos;
	pos.y += 150.0f;
	//�J�����̃|�W�V���������̃x�N�g�����擾�B
	CVector3 hp_angle;
	hp_angle = g_camera3D.GetPosition() - m_pos;
	hp_angle.y = 0;
	hp_angle.Normalize();
	//HP�̉摜���J�����Ɍ������đO�������悤�ɂ���B
	float angle = acos(hp_angle.Dot(m_Sprite_Front));
	angle = CMath::RadToDeg(angle);
	CVector3 hp_axis;
	hp_axis.Cross(m_Sprite_Front, hp_angle);
	if (hp_axis.y > 0) {
		m_Sprite_angle.SetRotationDeg(CVector3::AxisY(), angle);
	}
	else {
		m_Sprite_angle.SetRotationDeg(CVector3::AxisY()*-1, angle);
	}
	//HP�X�v���C�g�̍X�V
	m_enemyhp.Update(pos, m_Sprite_angle, { HP / 10, 1.0f, 1.0f });
	//HP�X�v���C�g�̕\��
	m_enemyhp.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
void TestEnemy::Update()
{
	CMatrix rotMatrix;
	rotMatrix.MakeRotationFromQuaternion(m_rot);
	m_forward.x = rotMatrix.m[2][0];
	m_forward.y = rotMatrix.m[2][1];
	m_forward.z = rotMatrix.m[2][2];
	m_forward.Normalize();
	m_timier++;
	m_pos = m_charaCon.Execute(1.0f / 30.0f, m_moveSpeed);
	if (m_timier >= 30) {
		FireBullets(800.0f);
		m_timier = 0;
	}
	if (m_bulletmaneger->kariget() == true)
	{
		HP -= 1.0f;
	}
	if (HP <= 0.0f)
	{
		DeleteGO(this);
	}
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);
}

void TestEnemy::Turn()
{
	//������ς���B
	if (fabsf(m_moveSpeed.x) > 0.1f
		|| fabsf(m_moveSpeed.z) > 0.1f) {
		auto angle = atan2f(m_moveSpeed.x, m_moveSpeed.z);
		m_rot.SetRotation(CVector3::AxisY(), angle);
	}
}

void TestEnemy::Draw()
{

	m_model.Draw(

		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);

}

void TestEnemy::PostDraw()
{
	HPGage();
}