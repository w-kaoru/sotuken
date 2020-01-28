#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "TestEnemy.h"
#include "Bullet/BulletManeger.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Light/DirectionLight.h"
#include "Title.h"
#include "Score.h"
#include "GameResults.h"
#include "TankData.h"
#include "level/Level.h"
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
	m_LigDirection = { 1.0f,-1.0f, 1.0f };
	m_LigDirection.Normalize();
	m_directionLight = NewGO<prefab::DirectionLight>(0, nullptr);
	m_directionLight->SetDirection(m_LigDirection);
	m_directionLight->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
}

bool Game::Start()
{
	int plNo = 0;
	m_backgeound = NewGO<BackGround>(1, "BackGround");
	m_level.Init(L"Assets/level/level_00.tkl", [&](LevelObjectData& objData) {
		if (objData.ForwardMatchName(L"Path_") == true) {
			//プレイヤー！！
			char playerName[15];
			sprintf(playerName, "Player_%d", plNo);
			Player* player = NewGO<Player>(0, playerName);
			player->SetNo(plNo);
			player->SetPosition(objData.position);
			m_playerList.push_back(player);
			if (plNo == 0) {
				m_gamecamera = NewGO<GameCamera>(1, "GameCamera");
				m_gamecamera->SetPlayer(player);
			}
			plNo++;
			return true;
		}
		return false;
	});
	m_testenemy = NewGO<TestEnemy>(1, "TestEnemy");
	m_bulletmaneger = NewGO<BulletManeger>(1, "BulletManeger");
	m_score = NewGO<Score>(1, "Score");
	return true;
}

void Game::OnDestroy()
{
	DeleteGO(m_backgeound);
	for (auto player : m_playerList) {
		if (player != nullptr) {
			DeleteGO(player);
		}
	}
	if (m_testenemy != nullptr) {
		DeleteGO(m_testenemy);
	}
	DeleteGO(m_bulletmaneger);
	DeleteGO(m_gamecamera);
	if (FindGO<TankData>("TankData") != nullptr) {
		DeleteGO(FindGO<TankData>("TankData"));
	}
}

void Game::Update()
{
	g_graphicsEngine->GetLightManager()->SetEyePos(m_gamecamera->GetCameraPos());


	if (m_time.GetSeconds() >= GameTime)
	{
		m_gameresults = NewGO<GameResults>(1, "GameResults");
		DeleteGO(this);

	}
	if (m_time.GetSeconds() >= CountDownTime)
	{
		for (auto player : m_playerList) {
			player->SetIsStop(false);
		}
		uuum = true;
	}

	if (m_testenemy->GetDeth() == true)
	{
		m_score->ScorePlus();
		DeleteGO(m_testenemy);
		m_testenemy = NewGO<TestEnemy>(1, "TestEnemy");
	}
	for (auto player : m_playerList) {
		/*if (m_player->GetPlayerDeth() == true)
		{
			m_score->DethPlus();
			DeleteGO(m_player);
			DeleteGO(m_gamecamera);
			m_player = NewGO<Player>(1, "Player");
			m_gamecamera = NewGO<GameCamera>(1, "GameCamera");
		}*/
	}
	CVector3 ligdir = m_LigDirection;
	ligdir *= -1.0f;
	ligdir.Normalize();
	ligdir *= 1000.0f;
	//ligdir += m_player->GetPosition();
	g_graphicsEngine->GetShadowMap()->UpdateFromLightTarget(
		ligdir,
		//m_player->GetPosition()
		CVector3::Zero()
	);
}

void Game::Draw()
{
	m_level.Draw();
}

void Game::PostDraw()
{
	//m_player->SetIsStop(true);
	int time;
	m_font.BeginDraw();
	m_time.TimerStop();
	time = (int)m_time.GetSeconds();
	if (uuum == true) {
		swprintf_s(moji, L"時間%03d秒", (GameTime - time));		//表示用にデータを加工
		m_font.Draw(
			moji,		//表示する文字列。
			{ -150.0f,FRAME_BUFFER_H / 2.0f },			//表示する座標。0.0f, 0.0が画面の中心。
			{ 1.0f,0.0f,0.0f,1.0f },
			0.0f,
			0.8f,
			{ 0.0f,1.0f }
		);
	}
	if (uuum == false) {
		swprintf_s(moji, L"%d", (CountDownTime - time));		//表示用にデータを加工
		m_font.Draw(
			moji,		//表示する文字列。
			{ -60.0f,60.0f },			//表示する座標。0.0f, 0.0が画面の中心。
			{ 0.0f,0.0f,0.0f,1.0f },
			0.0f,
			1.5f,
			{ 0.0f,1.0f }
		);
	}
	m_font.EndDraw();
}
