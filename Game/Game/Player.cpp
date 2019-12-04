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
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/pz4.cmo");
	m_playerhp.Init(L"Assets/sprite/hp_gauge.dds", 40.0f, 10.0f);
	//m_charaCon.Init(30.0f, 30.0f, m_pos);
	m_pos.x += 10000.0f;
	m_charaCon.Init({ 65.0f, 100.0f, 110.0f }, m_pos);
	m_charaCon.GetRigidBody()->GetBody()->setUserIndex(enCollisionAttr_Player);
	m_bulletmaneger = FindGO<BulletManeger>("BulletManeger");
	m_scale *= 0.5f;
	m_model.SetShadowReciever(true);
	return true;
}
void Player::FireBullets(float speed)
{
	
	Bullet* bullet = m_bulletmaneger->NewBullet(enCollisionAttr_PlayerBullet);
	bullet->SetMoveSpeed(m_forward * speed);
	CVector3 pos = m_pos;
	pos.y += 50.0f;
	bullet->SetPosition(pos);
}

void Player::HpGage()
{

	//HPスプライトの更新
	m_playerhp.Update({400.0f,300.0f,0.0f},CQuaternion::Identity(), { m_playerHP / 10, 1.0f, 1.0f });
	//HPスプライトの表示
	m_playerhp.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
}

void Player::Move()
{
	//左スティックの入力量を受け取る。
	 StX = g_pad[0].GetLStickYF();
	 StY = g_pad[0].GetLStickXF();
	//カメラの前方方向と右方向を取得
	CVector3 cameraForward = g_camera3D.GetForward();
	CVector3 cameraRight = g_camera3D.GetRight();
	//XZ平面での前方方向、右方向に変換する。
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
	if (m_bulletmaneger->GetPlayerDamage() == true &&m_playerHP > 0.0f)
	{
		m_playerHP -= m_bulletmaneger->GetBulletDamage();
	}
	//m_moveSpeed.y -= 10.0f;
	//m_pos = m_charaCon.Execute(1.0f / 30.0f, m_moveSpeed);
	m_pos = m_charaCon.Execute(1.0f / 30.0f, m_moveSpeed, m_rot);
	
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);
	//シャドウキャスターを登録。
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);
}

void Player::Turn()
{
	//向きを変える。
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

	HpGage();
}
