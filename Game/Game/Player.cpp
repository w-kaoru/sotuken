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
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_sprite.Init(L"Assets/sprite/title.dds", 1.0f, 1.0f);
	m_charaCon.Init(10.0f, 50.0f, m_pos);

	return true;
}
void Player::FireBullets(float speed)
{
	m_bulletmaneger = NewGO<BulletManeger>(1, "BulletManeger");
	CVector3 f = m_moveSpeed;
	f.Normalize();
	Bullet* bullet = m_bulletmaneger->NewBullet();
	bullet->SetMoveSpeed(m_forward * speed);
	CVector3 pos = m_pos;
	pos.y += 50.0f;
	bullet->SetPosition(pos);
}

void Player::Update()
{
	CMatrix rotMatrix/* = m_model.GetRotationMatrix()*/; 
	rotMatrix.MakeRotationFromQuaternion(m_rot);
	m_forward.x = rotMatrix.m[2][0];
	m_forward.y = rotMatrix.m[2][1];
	m_forward.z = rotMatrix.m[2][2];
	m_forward.Normalize();
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	//プレイヤーの移動処理。
	if (g_pad[0].IsPress(enButtonRight)) {
		//Dキーが押された。
		m_moveSpeed.x -= 50.0f;
	}
	if (g_pad[0].IsPress(enButtonLeft)) {
		//Aキーが押された。
		m_moveSpeed.x += 50.0f;
	}
	if (g_pad[0].IsPress(enButtonUp)) {
		//Wキーが押された。
		m_moveSpeed.z -= 50.0f;
	}
	if (g_pad[0].IsPress(enButtonDown)) {
		//Sキーが押された。
		m_moveSpeed.z += 50.0f;
	}
	if (g_pad[0].IsTrigger(enButtonA))
	{
		FireBullets(10.0f);
	}

	m_moveSpeed.y -= 10.0f;
	m_pos = m_charaCon.Execute(1.0 / 30.0, m_moveSpeed);
	//m_pos = m_moveSpeed;
	m_sprite.Update({ 0.0f,0.0f,0.0f }, CQuaternion::Identity(), CVector3::One());
	Turn();
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_pos, m_rot, CVector3::One());
}

void Player::Turn()
{
	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	m_rot.SetRotation(CVector3::AxisY(), angle);
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
		moji,		//表示する文字列。
		{ -100.0f,FRAME_BUFFER_H / 2.0f },			//表示する座標。0.0f, 0.0が画面の中心。
		{ 1.0f,0.0f,0.0f,1.0f },
		0.0f,
		m_fontsize,
		{ 0.0f,1.0f }
	);
	m_font.EndDraw();
}
