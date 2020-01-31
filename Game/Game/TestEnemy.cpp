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
	m_charaCon.RemoveRigidBoby();
	
}

bool TestEnemy::Start()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/pz4.cmo");
	m_enemyhp.Init(L"Assets/sprite/hp_gauge.dds", 40.0f, 10.0f);
	m_pos.x = 50.0f;
	m_pos.z = -500.0f;
	//m_charaCon.Init(30.0f, 50.0f, m_pos);
	m_charaCon.Init(
		{ 60.0f, 100.0f, 115.0f }, m_pos);
	m_charaCon.GetRigidBody()->GetBody()->setUserIndex(100);
	m_bulletmaneger = FindGO<BulletManeger>("BulletManeger");
	m_scale *= 0.5f;
	return true;
}

void TestEnemy::FireBullets(float speed)
{
	
	Bullet* bullet = m_bulletmaneger->NewBullet(enCollisionAttr_EnemyBullet, 100);
	bullet->SetMoveSpeed(m_forward * speed);
	CVector3 pos = m_pos;
	pos.y += 50.0f;
	bullet->SetPosition(pos);
}

void TestEnemy::Move()
{
	//���X�e�B�b�N�̓��͗ʂ��󂯎��B
	StY = g_pad[1].GetLStickYF();
	StX = g_pad[1].GetLStickXF();
	//�J�����̑O�������ƉE�������擾
	CVector3 cameraForward = g_camera3D.GetForward();
	CVector3 cameraRight = g_camera3D.GetRight();
	//XZ���ʂł̑O�������A�E�����ɕϊ�����B
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	m_moveSpeed += m_forward * StY * MOVE_SPEED;
	CVector3 vec = m_forward * StY + m_right * StX;
	if (vec.Length() > 0.0f)
	{
		vec.Normalize();
		float DotRes = vec.Dot(m_forward);
		if (fabsf(DotRes) < 0.9999f)
		{
			CVector3 axis;
			axis.Cross(m_forward, vec);
			axis.Normalize();
			float angle = acosf(min(1.0f, max(-1.0f, DotRes)));
			if (DotRes < 0.0)
			{
				axis *= -1.0f;
				angle = 3.14159f - angle;
			}

			angle *= 0.02f;
			CQuaternion qRot;
			qRot.SetRotation(axis, angle);
			m_rot.Multiply(qRot);

		}
	}

	m_moveSpeed.y += -1800.0f * m_deltatime;
}

void TestEnemy::HPGage()
{
	//�|�W�V�����𓪂̏�t�߂ɂ���B
	auto pos = m_pos;
	pos.y += 150.0f;
	//HP�X�v���C�g�̍X�V
	m_enemyhp.Update(pos, g_camera3D.GetViewRotationMatrix(), { HP / 10, 1.0f, 1.0f });
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
	m_right.x = rotMatrix.m[0][0];
	m_right.y = rotMatrix.m[0][1];
	m_right.z = rotMatrix.m[0][2];
	m_right.Normalize();
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_timier++;
	Move();
	m_pos = m_charaCon.Execute(1.0f / 30.0f, m_moveSpeed, m_rot);
	if (m_timier >=20.0f && g_pad[1].IsTrigger(enButtonA)) {
		FireBullets(800.0f);
		m_timier = 0;
	}
	if (m_bulletmaneger->GetDamageFlag() == true)
	{
		HP -= m_bulletmaneger->GetBulletDamage();
		m_bulletmaneger->SetDamegeFlag(false);
	}
	if (HP <= 0.0f)
	{
		enemydeth = true;
	}
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);
	//�V���h�E�L���X�^�[��o�^�B
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);
}

void TestEnemy::Turn()
{
	////������ς���B
	//if (fabsf(m_moveSpeed.x) > 0.1f
	//	|| fabsf(m_moveSpeed.z) > 0.1f) {
	//	auto angle = atan2f(m_moveSpeed.x, m_moveSpeed.z);
	//	m_rot.SetRotation(CVector3::AxisY(), angle);
	//}
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