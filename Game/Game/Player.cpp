#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "BulletManeger.h"
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
	m_sprite.Init(L"Assets/sprite/title.dds", 1.0f, 1.0f);
	return true;
}
void Player::FireBullets()
{
	m_bulletmaneger = NewGO<BulletManeger>(1, "BulletManeger");
	CMatrix rotMatrix = m_model.GetRotationMatrix();
	CVector3 forward;
	forward.x = rotMatrix.m[2][0];
	forward.y = rotMatrix.m[2][1];
	forward.z = rotMatrix.m[2][2];
	Bullet* bullet = m_bulletmaneger->NewBullet();
	bullet->SetMoveSpeed(forward*10.0f);
	CVector3 pos = m_pos;
	pos.y += 50.0f;
	bullet->SetPosition(pos);
}
void Player::Update()
{
	if (g_pad[0].IsTrigger(enButtonA))
	{
		FireBullets();
	}
	m_sprite.Update({ 0.0f,0.0f,0.0f }, CQuaternion::Identity(), CVector3::One());
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
}
void Player::Draw()
{
	
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}

void Player::PostDraw()
{
	m_sprite.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
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
