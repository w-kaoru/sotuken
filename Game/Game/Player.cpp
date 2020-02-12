#include "stdafx.h"
#include"Game.h"
#include "Player.h"
#include "Physics/CollisionAttr.h"
#include "Bullet/Bullet.h"
#include "Bullet/BulletManeger.h"
#include "TankInfo.h"
#include "TankData.h"
#include "GameCamera.h"
#include "UI.h"
#include "BulletTypeChange.h"
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
	m_bulletChange = NewGO<BulletTypeChange>(1, "BulletTypeChange");
	m_bulletChange->BulletSelect(BulletType::HE);
	m_movese = NewGO<prefab::CSoundSource>(0);
	m_movese->Init(L"Assets/sound/running-tank-1.wav", false);
	m_movese->SetVolume(0.3f);

	g_gameCamera3D[m_number]->SetCameraSpeed(m_tankData->GetTankDeta()->cameraturn);
	g_gameCamera3D[m_number]->SetNumber(m_number);
	char uiName[20];
	sprintf(uiName, "UI_%d", m_number);
	m_ui = NewGO<UI>(1, uiName);
	m_ui->SetHP(m_tankData->GetTankDeta()->hp);
	m_ui->SetAimingScale(CVector3::One());
	m_ui->SetNumber(m_number);
	m_ui->SetBulletChange(m_bulletChange);

	//cmoファイルの読み込み。
	m_model.Init(m_tankData->GetTankDeta()->filePath_00);
	m_model2.Init(m_tankData->GetTankDeta()->filePath_01);
	m_charaCon.Init(m_tankData->GetTankDeta()->BOXLength, m_pos);
	m_charaCon.GetRigidBody()->GetBody()->setUserIndex(enCollisionAttr_Players + m_number);
	m_charaCon.SetPlayerNumber(m_number);
	m_bulletmaneger = FindGO<BulletManeger>("BulletManeger");
	m_bulletmaneger->SetBulletDamage(m_bulletChange->GetTankBulletInfo()->bulletdamage);
	m_scale *= m_tankData->GetTankDeta()->scale;

	m_game = FindGO<Game>("Game");
	//シャドウキャスターを登録。
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model2);
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);
	m_model2.UpdateWorldMatrix(m_pos, m_rotation, m_scale);
	if (m_game->GetMoveFlag() == false)
	{
		this->SetIsStop(true);
	}
	m_playerHP = max(0, m_tankData->GetTankDeta()->hp);
	m_smokeEffect = Effekseer::Effect::Create(g_graphicsEngine->GetEffekseerManager(),
		(const EFK_CHAR*)L"Assets/effect/smoke.efk");
	return true;
}

void Player::OnDestroy()
{
	if (m_ui != nullptr) DeleteGO(m_ui);
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
	Bullet* bullet = m_bulletmaneger->NewBullet(enCollisionAttr_PlayerBullet, m_number);
	bullet->SetMoveSpeed(g_gameCamera3D[m_number]->GetForward() * m_bulletChange->GetTankBulletInfo()->bulletSpeed);
	CVector3 pos = m_pos;
	pos.y += 90.0f;
	m_smokeEffectHandle = g_graphicsEngine->GetEffekseerManager()->Play(
		m_smokeEffect, m_gunForward.x, m_gunForward.y, m_gunForward.z
	);
	bullet->SetPosition(m_gunForward);
}

void Player::Move()
{
	//左スティックの入力量を受け取る。
	StY = g_pad[m_number].GetLStickYF();
	StX = g_pad[m_number].GetLStickXF();
	if (g_pad[m_number].GetLStickYF() >= 0.001f ||
		g_pad[m_number].GetLStickYF() <= -0.001f)
	{
		m_movese->Play(true);
		m_moveEffectHandle = g_graphicsEngine->GetEffekseerManager()->Play(
			m_smokeEffect, m_pos.x, m_pos.y - 5.0f, m_pos.z
		);
	}
	else
	{
		m_movese->Stop();
	}
	//カメラの前方方向と右方向を取得
	CVector3 cameraForward = g_gameCamera3D[m_number]->GetCamera().GetForward();
	CVector3 cameraRight = g_gameCamera3D[m_number]->GetCamera().GetRight();
	//XZ平面での前方方向、右方向に変換する。
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	/*m_moveSpeed += m_forward * StX * MOVE_SPEED * m_deltatime;
	m_moveSpeed += m_right * StX*MOVE_SPEED * m_deltatime;*/
	m_moveSpeed += m_forward * StY * m_tankData->GetTankDeta()->speed * m_downSpeed;
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

	m_movese->SetPosition(m_pos);
	g_gameCamera3D[m_number]->SetCameraTarget(m_pos);

	if (g_pad[m_number].IsPress(enButtonLB2)) {
		g_gameCamera3D[m_number]->SetAimFlag(true);
		m_ui->SetAimingScale({ 5.0f,5.0f,5.0f });
	}
	else
	{
		g_gameCamera3D[m_number]->SetAimFlag(false);
		m_ui->SetAimingScale(CVector3::One());
	}

	if (g_pad[m_number].IsTrigger(enButtonRight)) {
		int bnum = m_bulletChange->GetBulletType() + 1;
		if (BulletType::num == bnum) {
			bnum = 0;
		}
		m_bulletChange->BulletSelect((BulletType)bnum);
	}
	if (g_pad[m_number].IsTrigger(enButtonLeft)) {
		int bnum = m_bulletChange->GetBulletType() - 1;
		if (bnum <= -1) {
			bnum = BulletType::num;
			bnum--;
		}
		m_bulletChange->BulletSelect((BulletType)bnum);
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
	if (m_timier >= 30.0f&&g_pad[m_number].IsTrigger(enButtonRB2))
	{
		FireBullets(800.0f);
		m_timier = 0;
	}
	if (m_bulletmaneger->GetDamageFlag() == true &&
		m_bulletmaneger->GetNumber() != m_number &&
		m_bulletmaneger->GetHitNumber() == m_charaCon.GetPlayerNumber())
	{
		char playerName[15];
		sprintf(playerName, "Player_%d", m_bulletmaneger->GetNumber());
		Player* player = FindGO<Player>(playerName);
		if (player->GetBulletChange()->GetBulletType() == BulletType::AP) {
			m_downSpeed *= 0.7f;
			m_downSpeed = min(1.0f, m_downSpeed);
			m_downSpeed = max(0.1f, m_downSpeed);
		}
		m_playerHP -= player->GetBulletChange()->GetTankBulletInfo()->bulletdamage - m_tankData->GetTankDeta()->defense;
		m_bulletmaneger->SetDamegeFlag(false);

	}
		m_ui->SetHP(m_playerHP);
	if (m_playerHP <= 0.0f || m_pos.y <= -1000.0f)
	{
		playerdeth = true;
	}
	m_ui->SetHP(m_playerHP);
	m_pos = m_charaCon.Execute(1.0f / 30.0f, m_moveSpeed, m_rot);

	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);
	m_model2.UpdateWorldMatrix(m_pos, m_rotation, m_scale);
	//シャドウキャスターを登録。
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model2);

	g_graphicsEngine->GetLightManager()->SetEyePos(g_gameCamera3D[m_number]->GetCameraPos());
}

void Player::Turn()
{
	//向きを変える。
	auto angle = atan2f(g_gameCamera3D[m_number]->GetCamera().GetForward().x,
		g_gameCamera3D[m_number]->GetCamera().GetForward().z);
	m_rotation.SetRotation(CVector3::AxisY(), angle);
}

void Player::Draw()
{
	/*m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
	m_model2.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);*/
}

void Player::Draw(int player_num)
{

	m_model.Draw(
		enRenderMode_Normal,
		g_gameCamera3D[player_num]->GetCamera().GetViewMatrix(),
		g_gameCamera3D[player_num]->GetCamera().GetProjectionMatrix()
	);
	m_model2.Draw(
		enRenderMode_Normal,
		g_gameCamera3D[player_num]->GetCamera().GetViewMatrix(),
		g_gameCamera3D[player_num]->GetCamera().GetProjectionMatrix()
	);
}
