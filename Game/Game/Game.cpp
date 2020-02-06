#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "TestEnemy.h"
#include "Bullet/BulletManeger.h"
#include "BackGround.h"
#include "Light/DirectionLight.h"
#include "Title.h"
#include "Score.h"
#include "GameResults.h"
#include "Sky.h"
#include "TankData.h"
#include "level/Level.h"
#include "GameCamera.h"
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
	m_sky = NewGO<Sky>(1, "Sky");
	m_level.Init(L"Assets/level/level_00.tkl", [&](LevelObjectData& objData) {
		//player_totalの人数だけプレイヤーを生成。
		if (plNo < player_total) {
			if (objData.ForwardMatchName(L"Path_") == true) {
				//マップに配置された全てのプレイヤーのインスタンスを出す。
				char playerName[15];
				sprintf(playerName, "Player_%d", plNo);
				Player* player = NewGO<Player>(0, playerName);
				player->SetNumber(plNo);
				player->SetPosition(objData.position);
				m_Nanka.push_back(objData.position);
				m_playerList.push_back(player);
				plNo++;
				//ゲームカメラ

				return true;
			}
		}
		return false;
	});

	//ゲームカメラのビューポートの設定。
	int l_half_w = FRAME_BUFFER_W / 2;
	int l_half_h = FRAME_BUFFER_H / 2;
	switch (player_total)
	{
	case 1://プレイヤーが1人
		g_gameCamera3D[0]->SetViewPort({ 0, 0, (l_half_w*2), (l_half_h*2) });
		break;
	case 2://プレイヤーが2人
		g_gameCamera3D[0]->SetViewPort({ 0, 0, l_half_w, (l_half_h*2) });
		g_gameCamera3D[1]->SetViewPort({ l_half_w, 0, l_half_w, (l_half_h*2) });
		break;
	case 3://プレイヤーが3人
		g_gameCamera3D[0]->SetViewPort({ 0, 0, l_half_w, l_half_h });
		g_gameCamera3D[1]->SetViewPort({ l_half_w, 0, l_half_w, l_half_h });
		g_gameCamera3D[2]->SetViewPort({ 0, l_half_h, l_half_w, l_half_h });
		break;
	case 4://プレイヤーが4人
		g_gameCamera3D[0]->SetViewPort({ 0, 0, l_half_w, l_half_h });
		g_gameCamera3D[1]->SetViewPort({ l_half_w, 0, l_half_w, l_half_h });
		g_gameCamera3D[2]->SetViewPort({ 0, l_half_h, l_half_w, l_half_h });
		g_gameCamera3D[3]->SetViewPort({ l_half_w, l_half_h, l_half_w, l_half_h });
		break;
	default:
		break;
	}
	GameEngine::GetViewSplit().Start();//分割開始。
	//m_testenemy = NewGO<TestEnemy>(1, "TestEnemy");
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
	if (FindGO<TankData>("TankData") != nullptr) {
		DeleteGO(FindGO<TankData>("TankData"));
	}

	//ビューポートのリセット。
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		g_gameCamera3D[i]->FinishViewPort();
	}
}

void Game::Update()
{
	if (m_time.GetSeconds() >= GameTime)
	{
		m_gameresults = NewGO<GameResults>(1, "GameResults");
		DeleteGO(this);

	}

	if (m_testenemy->GetDeth() == true)
	{
		m_score->ScorePlus();
		DeleteGO(m_testenemy);
		m_testenemy = NewGO<TestEnemy>(1, "TestEnemy");
	}
	for (auto player : m_playerList) {
		if (m_time.GetSeconds() >= CountDownTime)
		{
			player->SetIsStop(false);
			MoveFlag = true;
		}
		if (player->GetPlayerDeth() == true)
		{
			m_score->DethPlus();
			DeleteGO(player);
			CVector3 pos = m_Nanka.at(player->GetNumber());
			int no = player->GetNumber();
			m_playerList.erase(std::remove(m_playerList.begin(), m_playerList.end(), player), m_playerList.end());
			player = NewGO<Player>(0, "Player");
			player->SetPosition(pos);
			player->SetNumber(no);
		}
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
	m_time.TimerStop();
	m_font.BeginDraw();
	time = (int)m_time.GetSeconds();
	if (MoveFlag == true) {
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
	if (MoveFlag == false) {
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
