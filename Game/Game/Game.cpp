#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "TestEnemy.h"
#include "Bullet/BulletManeger.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Light/DirectionLight.h"
#include "Title.h"

Game::Game()
{
	InitLight();
	m_testbgm.Init(L"Assets/sound/coinGet.wav");
	//m_testbgm.Play(true);
	m_time.TimerStart();
	m_testEffect = Effekseer::Effect::Create(g_graphicsEngine->GetEffekseerManager(),
		(const EFK_CHAR*)L"Assets/effect/test.efk");
}


Game::~Game()
{
}

void Game::InitLight()
{
	//ライトを配置。
	m_LigDirection = { 1.0f, -1.0f, 0.0f };
	m_LigDirection.Normalize();
	m_directionLight = NewGO<prefab::DirectionLight>(0, nullptr);
	m_directionLight->SetDirection(m_LigDirection);
	m_directionLight->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
}

bool Game::Start()
{
	m_backgeound = NewGO<BackGround>(1, "BackGround");
	m_player = NewGO<Player>(1, "Player");
	m_testenemy = NewGO<TestEnemy>(1, "TestEnemy");
	m_bulletmaneger = NewGO<BulletManeger>(1, "BulletManeger");
	m_gamecamera = NewGO<GameCamera>(1, "GameCamera");
	return true;
}

void Game::OnDestroy()
{
	DeleteGO(m_backgeound);
	DeleteGO(m_player);
	if (m_testenemy->GetDeth() == false) {
		DeleteGO(m_testenemy);
	}
	DeleteGO(m_bulletmaneger);
	DeleteGO(m_gamecamera);
}

void Game::Update()
{
	g_graphicsEngine->GetLightManager()->SetEyePos(m_gamecamera->GetCameraPos());


	if (g_pad[0].IsTrigger(enButtonB))
	{
		//DeleteGO(this);
		//NewGO<Title>(0, "title");
		//m_time.TimerStop();

	}
	CVector3 ligdir = m_LigDirection;
	ligdir *= -1.0f;
	ligdir.Normalize();
	ligdir *= 4000.0f;
	ligdir += m_player->GetPosition();
	g_graphicsEngine->GetShadowMap()->UpdateFromLightTarget(
		ligdir,
		m_player->GetPosition()
	);
}

void Game::Draw()
{

}

void Game::PostDraw()
{
	int time;
	m_font.BeginDraw();
	m_time.TimerStop();
	time = (int)m_time.GetSeconds();
	swprintf_s(moji, L"時間%03d秒", time);		//表示用にデータを加工
	m_font.Draw(
		moji,		//表示する文字列。
		{ -200.0f,FRAME_BUFFER_H / 2.0f },			//表示する座標。0.0f, 0.0が画面の中心。
		{ 1.0f,0.0f,0.0f,1.0f },
		0.0f,
		1.0f,
		{ 0.0f,1.0f }
	);
	m_font.EndDraw();
}
