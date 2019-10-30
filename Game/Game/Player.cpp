#include "stdafx.h"
#include "Player.h"
#include "Physics/CollisionAttr.h"
#include "Bullet/Bullet.h"
#include "Bullet/BulletManeger.h"
#include "Define.h"
Player::Player()
{
}


Player::~Player()
{
}

bool Player::Start()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_charaCon.Init(20.0f, 50.0f, m_pos);
	m_charaCon.GetRigidBody()->GetBody()->setUserIndex(enCollisionAttr_Player);
	m_bulletmaneger = FindGO<BulletManeger>("BulletManeger");
	return true;
}
void Player::FireBullets(float speed)
{
	
	Bullet* bullet = m_bulletmaneger->NewBullet();
	bullet->SetMoveSpeed(m_forward * speed);
	CVector3 pos = m_pos;
	pos.y += 50.0f;
	bullet->SetPosition(pos);
}

void Player::Move()
{
	//���X�e�B�b�N�̓��͗ʂ��󂯎��B
	 StX = g_pad[0].GetLStickYF();
	 StY = g_pad[0].GetLStickXF();
	//�J�����̑O�������ƉE�������擾
	CVector3 cameraForward = g_camera3D.GetForward();
	CVector3 cameraRight = g_camera3D.GetRight();
	//XZ���ʂł̑O�������A�E�����ɕϊ�����B
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	m_moveSpeed += cameraForward * StX * MOVE_SPEED * m_deltatime;
	m_moveSpeed += cameraRight * StY * MOVE_SPEED * m_deltatime;
	m_moveSpeed.y += -1800.0f * m_deltatime;
}

void Player::Update()
{
	CMatrix rotMatrix; 
	rotMatrix.MakeRotationFromQuaternion(m_rot);
	m_forward.x = rotMatrix.m[2][0];
	m_forward.y = rotMatrix.m[2][1];
	m_forward.z = rotMatrix.m[2][2];
	m_forward.Normalize();
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	Move();
	Turn();
	if (g_pad[0].IsTrigger(enButtonA))
	{
		FireBullets(800.0f);
	}

	//m_moveSpeed.y -= 10.0f;
	m_pos = m_charaCon.Execute(1.0f / 30.0f, m_moveSpeed);
	
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);
}

void Player::Turn()
{
	//������ς���B
	if (fabsf(m_moveSpeed.x) > 0.1f
		|| fabsf(m_moveSpeed.z) > 0.1f) {
		auto angle = atan2f(m_moveSpeed.x, m_moveSpeed.z);
		m_rot.SetRotation(CVector3::AxisY(), angle);
	}
}

void Player::Draw()
{
	
	m_model.Draw(

		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}

void Player::PostDraw()
{
	m_font.BeginDraw();
	swprintf_s(moji, L"HELLO");
	m_font.Draw
	(
		moji,		//�\�����镶����B
		{ -100.0f,FRAME_BUFFER_H / 2.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
		{ 1.0f,0.0f,0.0f,1.0f },
		0.0f,
		m_fontsize,
		{ 0.0f,1.0f }
	);
	m_font.EndDraw();
}
