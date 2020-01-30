#include "stdafx.h"
#include"Game.h"
#include "Player.h"
#include "Physics/CollisionAttr.h"
#include "Bullet/Bullet.h"
#include "Bullet/BulletManeger.h"
#include "TankInfo.h"
#include "TankData.h"
#include "GameCamera.h"
//#include "Define.h"

Player::Player()
{
}


Player::~Player()
{
	m_charaCon.RemoveRigidBoby();
	playerdeth = false;
}

bool Player::Start()
{
	m_tankData = FindGO<TankData>("TankData");
	m_tankData->BulletSelect(BulletType::HE);
	if (m_number == 0) {//今だけ、カメラは一つしかないので0番目のみ。
		char gameCameraName[20];
		sprintf(gameCameraName, "GameCamera_%d", m_number);
		m_gamecamera = NewGO<GameCamera>(0, gameCameraName);
		m_gamecamera->SetCameraPos({ m_pos.x,m_pos.y + 130.0f,m_pos.z + 250.0f });
		m_gamecamera->SetTarget(m_pos);
		m_gamecamera->SetCameraSpeed(m_tankData->GetTankDeta()->cameraturn);
	}
	//cmoファイルの読み込み。
	m_model.Init(m_tankData->GetTankDeta()->filePath_00);
	m_model2.Init(m_tankData->GetTankDeta()->filePath_01);
	m_playerhp.Init(L"Assets/sprite/hp_gauge.dds", 40.0f, 10.0f);
	m_aiming.Init(L"Assets/sprite/aiming.dds",100.0f,100.0f);
	m_bulletsprite.Init(L"Assets/sprite/bullet.dds", 150.0f, 150.0f);
	m_charaCon.Init(m_tankData->GetTankDeta()->BOXLength, m_pos);
	m_charaCon.GetRigidBody()->GetBody()->setUserIndex(enCollisionAttr_Players + m_number);
	m_bulletmaneger = FindGO<BulletManeger>("BulletManeger");
	m_scale *= m_tankData->GetTankDeta()->scale;
	auto angle = atan2f(g_camera3D.GetForward().x, g_camera3D.GetForward().z);
	m_rotation.SetRotation(CVector3::AxisY(), angle);
	m_tankData->BulletSelect(BulletType::HE);
	m_bulletmaneger->SetBulletDamage(m_tankData->GetTankDeta()->bulletdamage);
	m_rot = m_rotation;
	/*m_model.SetShadowReciever(true);
	m_model2.SetShadowReciever(true);*/
	m_game = FindGO<Game>("Game");
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);
	m_model2.UpdateWorldMatrix(m_pos, m_rotation, m_scale);
	//シャドウキャスターを登録。
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model2);
	if (m_game->GetMoveFlag() == false)
	{
		this->SetIsStop(true);
	}
	m_playerHP = max(0, m_tankData->GetTankDeta()->hp);
	
	return true;
}

void Player::OnDestroy()
{
	DeleteGO(m_gamecamera);
}

void Player::FireBullets(float speed)
{
	CMatrix rotMatrix;
	rotMatrix.MakeRotationFromQuaternion(m_rotation);
	m_gunForward.x = rotMatrix.m[2][0];
	m_gunForward.y = rotMatrix.m[2][1];
	m_gunForward.z = rotMatrix.m[2][2];
	m_gunForward.Normalize();
	m_gunForward = m_gunForward * 90.0f;
	m_gunForward += m_pos;
	m_gunForward.y = 45.0f;
	Bullet* bullet = m_bulletmaneger->NewBullet(enCollisionAttr_PlayerBullet,m_number);
	bullet->SetMoveSpeed(g_camera3D.GetForward() * m_tankData->GetTankDeta()->bulletSpeed);
	CVector3 pos = m_pos;
	pos.y += 90.0f;
	bullet->SetPosition(m_gunForward);
}

void Player::HpGage()
{
	//HPスプライトの更新
	m_playerhp.Update({400.0f,300.0f,0.0f},CQuaternion::Identity(), { m_playerHP / 10.0f, 1.0f, 1.0f });
	//HPスプライトの表示
	m_playerhp.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
}

void Player::Aiming()
{
	m_aimingpos.y = -20.0f;
	m_aiming.Update(m_aimingpos, CQuaternion::Identity(),m_aimingSpriteScale);
	m_aiming.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	if (m_timier <= 20)
	{
		m_aiming.SetColor({ 1.0f,0.0f,0.0f,1.0f });
	}
	else
	{
		m_aiming.SetColor({ 0.0f,0.0f,0.0f,1.0f });
	}
}

void Player::BulletSprite()
{

		m_bulletsprite.Update({ -450.0f,-250.0f,0.0f }, CQuaternion::Identity(), CVector3::One());
		m_bulletsprite.Draw(
			g_camera2D.GetViewMatrix(),
			g_camera2D.GetProjectionMatrix()
		);
	switch (m_tankData->GetBulletType())
	{
	case HE:
		m_bulletsprite.SetColor({0.0f,0.0f,0.0f,1.0f });
		break;
	case AP:
		m_bulletsprite.SetColor({ 0.0f,1.0f,0.0f,1.0f });
		break;
	}

}

void Player::Move()
{
	//左スティックの入力量を受け取る。
	 StY = g_pad[m_number].GetLStickYF();
	 StX = g_pad[m_number].GetLStickXF();
	//カメラの前方方向と右方向を取得
	CVector3 cameraForward = g_camera3D.GetForward();
	CVector3 cameraRight = g_camera3D.GetRight();
	//XZ平面での前方方向、右方向に変換する。
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	/*m_moveSpeed += m_forward * StX * MOVE_SPEED * m_deltatime;
	m_moveSpeed += m_right * StX*MOVE_SPEED * m_deltatime;*/
	m_moveSpeed += m_forward * StY * m_tankData->GetTankDeta()->speed;
	CVector3 vec = m_forward * StY + m_right * StX;
	if (vec.Length() > 0.0f)
	{
		vec.Normalize();
		float DotRes = vec.Dot(m_forward);
		if (fabsf(DotRes) < 0.990f)
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
			
			angle *= m_tankData->GetTankDeta()->bodyturn;
			CQuaternion qRot;
			qRot.SetRotation(axis, angle);
			m_rot.Multiply(qRot);
			
		}
	}
	
	m_moveSpeed.y += -1800.0f * m_deltatime;
}

void Player::Update()
{
	if (m_number == 0) {//今だけ、カメラは一つしかないので0番目のみ。
		m_gamecamera->SetTarget(m_pos);

		if (g_pad[m_number].IsPress(enButtonLB2)) {
			m_gamecamera->SetAimFlag(true);
			m_aimingSpriteScale = { 5.0f ,5.0f ,5.0f };
		}
		else
		{
			m_gamecamera->SetAimFlag(false);
			m_aimingSpriteScale = CVector3::One();
		}
	}

	if (g_pad[m_number].IsTrigger(enButtonRight)) {
		int bnum = m_tankData->GetBulletType() + 1;
		if (BulletType::num == bnum) {
			bnum = 0;
		}
		m_tankData->BulletSelect((BulletType)bnum);
	}
	if (g_pad[m_number].IsTrigger(enButtonLeft)) {
		int bnum = m_tankData->GetBulletType() - 1;
		if (bnum <= -1) {
			bnum = BulletType::num;
			bnum--;
		}
		m_tankData->BulletSelect((BulletType)bnum);
	}
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
	Turn();
	if (m_timier >= 20.0f&&g_pad[m_number].IsTrigger(enButtonRB2))
	{
			FireBullets(800.0f);
			m_timier = 0;
	}
	if (m_bulletmaneger->GetDamageFlag() == true &&
		m_bulletmaneger->GetNumber() != m_number)
	{
		m_playerHP -= m_bulletmaneger->GetBulletDamage() - m_tankData->GetTankDeta()->defense;
		m_bulletmaneger->SetDamegeFlag(false);
	}
	if (m_playerHP <= 0.0f)
	{
		playerdeth = true;
	}
	m_pos = m_charaCon.Execute(1.0f / 30.0f, m_moveSpeed, m_rot);
	
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);
	m_model2.UpdateWorldMatrix(m_pos, m_rotation, m_scale);
	//シャドウキャスターを登録。
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model2);

	g_graphicsEngine->GetLightManager()->SetEyePos(m_gamecamera->GetCameraPos());

}

void Player::Turn()
{
	//向きを変える。
	auto angle = atan2f(g_camera3D.GetForward().x, g_camera3D.GetForward().z);
	m_rotation.SetRotation(CVector3::AxisY(), angle);
}

void Player::Draw()
{
	
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
	m_model2.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Player::PostDraw()
{
	HpGage();
	Aiming();
	BulletSprite();
	m_font.BeginDraw();
	switch (m_tankData->GetBulletType())
	{
		case HE:
			swprintf_s(moji, L"HE弾");		//表示用にデータを加工
		break;
		case AP:
			swprintf_s(moji, L"AP弾");		//表示用にデータを加工
			break;
	}
	m_font.Draw(
		moji,		//表示する文字列。
		{ -500.0f,-200.0f },			//表示する座標。0.0f, 0.0が画面の中心。
		{ 1.0f,0.0f,0.0f,1.0f },
		0.0f,
		0.8f,
		{ 0.0f,1.0f }
	);
	m_font.EndDraw();
}
