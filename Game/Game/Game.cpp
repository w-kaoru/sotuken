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
#include "Sky.h"
#include "TankData.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Score.h"

Game::Game()
{
	InitLight();
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
	
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		g_gameCamera3D[i] = NewGO<GameCamera>(1, "GameCamera");
	}
	//ゲームカメラのビューポートの設定。
	int l_half_w = FRAME_BUFFER_W / 2;
	int l_half_h = FRAME_BUFFER_H / 2;
	switch (player_total)
	{
	case 1://プレイヤーが1人
		g_gameCamera3D[0]->SetViewPort({ 0, 0, (l_half_w * 2), (l_half_h * 2) });
		break;
	case 2://プレイヤーが2人
		g_gameCamera3D[0]->SetViewPort({ 0, 0, l_half_w, (l_half_h * 2) });
		g_gameCamera3D[1]->SetViewPort({ l_half_w, 0, l_half_w, (l_half_h * 2) });
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
	for (int i = 0; i < player_total; i++)
	{
		g_gameCamera3D[i]->Get_isViewport();
	}
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
				m_respawnpos.push_back(objData.position);
				m_playerList.push_back(player);
				//ゲームカメラの初期化。
				//g_gameCamera3D[plNo]->SetCameraPos({ player->GetPosition().x,player->GetPosition().y + 250.0f,player->GetPosition().z + 150.0f });
				g_gameCamera3D[plNo]->SetPosition({ player->GetPosition().x,player->GetPosition().y,player->GetPosition().z + 150.0f });
				g_gameCamera3D[plNo]->SetTarget(player->GetPosition());
				g_gameCamera3D[plNo]->SetNumber(plNo);
				char scoreName[15];
				sprintf(scoreName, "Score_%d", plNo);
				Score* score = NewGO<Score>(0, scoreName);
				score->SetName(playerName);
				m_scoreList.push_back(score);
				plNo++;
				return true;
			}
		}
		return true;
	});
	GameEngine::GetViewSplit().Start();//分割開始。
	//m_testenemy = NewGO<TestEnemy>(1, "TestEnemy");
	m_bulletmaneger = NewGO<BulletManeger>(1, "BulletManeger");
	//m_score = NewGO<Score>(1, "Score");
	return true;
}

void Game::OnDestroy()
{
	DeleteGO(m_backgeound);
	for (auto player : m_playerList) {
		if (player != nullptr) {
			DeleteGO(player);
			//m_playerList.erase(std::remove(m_playerList.begin(), m_playerList.end(), player), m_playerList.end());
		}
	}
	for (auto player : m_playerList) {
		if (!player) {
			m_playerList.erase(std::remove(m_playerList.begin(), m_playerList.end(), player), m_playerList.end());
		}
	}
	//if (m_testenemy != nullptr) {
	//	DeleteGO(m_testenemy);
	//}
	if (m_bulletmaneger != nullptr) {
		DeleteGO(m_bulletmaneger);
	}
	for (int i = 0; i < player_total; i++) {
		char tankDataName[15];
		sprintf(tankDataName, "TankData_%d", i);
		if (FindGO<TankData>(tankDataName) != nullptr) {
			DeleteGO(FindGO<TankData>(tankDataName));
		}
	}

	//ビューポートのリセット。
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		//g_gameCamera3D[i]->FinishViewPort();
		DeleteGO(g_gameCamera3D[i]);
		GetViewSplit().Finish();
	}
}

void Game::Update()
{


	if (m_time.GetSeconds() >= GameTime)
	{

		Endflag = true;
		GameEndtime++;
		if (GameEndtime >= 60)
		{
			m_gameresults = NewGO<GameResults>(1, "GameResults");
			m_gameresults->SetScoreList(m_scoreList);
			DeleteGO(this);
		}
	}
	CVector3 pos;
	int num;
	for (auto player : m_playerList) {
		if (m_time.GetSeconds() >= CountDownTime && MoveFlag == false)
		{
			player->SetIsStop(false);
			m_moveCount++;
			if (m_moveCount >= player_total) {
				MoveFlag = true;
			}
		}
		if (player->GetPlayerDeth() == true)
		{
			m_isDeth = true;
			m_scoreList.at(player->GetNumber())->DethPlus();
			if (player->GetTankDamageNumber() < player_total) {
				m_scoreList.at(player->GetTankDamageNumber())->KillPlus();
			}
			pos = m_respawnpos.at(player->GetNumber());
			num = player->GetNumber();
			DeleteGO(player);
			m_playerList.erase(std::remove(m_playerList.begin(), m_playerList.end(), player), m_playerList.end());
			//player = nullptr;
		}
	}
	for (auto player : m_playerList)
	{
		if (!player)
		{
			m_playerList.erase(std::remove(m_playerList.begin(), m_playerList.end(), player), m_playerList.end());
		}
	}

	if (m_isDeth) {
		char playerName[15];
		sprintf(playerName, "Player_%d", num);
		Player* pplayer = NewGO<Player>(0, playerName);
		pplayer->SetNumber(num);
		pplayer->SetPosition(pos);
		m_playerList.push_back(pplayer);
		m_isDeth = false;
	}
	CVector3 ligdir = m_LigDirection;
	ligdir *= -1.0f;
	ligdir.Normalize();
	ligdir *= 2000.0f;
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

void Game::PostDraw(int player_num)
{
	int time;
	m_time.TimerStop();
	m_font.BeginDraw();
	time = (int)m_time.GetSeconds();
	if (MoveFlag == true) {
		switch (player_total)
		{
		case 1://1人。
			swprintf_s(moji, L"時間%03d秒", (GameTime - time));		//表示用にデータを加工
			m_font.Draw(
				moji,		//表示する文字列。
				{ -150.0f,FRAME_BUFFER_H / 2.0f },			//表示する座標。0.0f, 0.0が画面の中心。
				{ 1.0f,0.0f,0.0f,1.0f },
				0.0f,
				0.8f,
				{ 0.0f,1.0f }
			);
			break;
		case 2://2人。
			swprintf_s(moji, L"時間%03d秒", (GameTime - time));		//表示用にデータを加工
			m_font.Draw(
				moji,		//表示する文字列。
				{ -420.0f, 350.0f },			//表示する座標。0.0f, 0.0が画面の中心。
				{ 1.0f,0.0f,0.0f,1.0f },
				0.0f,
				0.8f/2.0f,
				{ 0.0f,1.0f }
			);
			break;
		case 3:
		case 4:
			//3人以上。
			swprintf_s(moji, L"時間%03d秒", (GameTime - time));		//表示用にデータを加工
			m_font.Draw(
				moji,		//表示する文字列。
				{ -350.0f,360.0f },			//表示する座標。0.0f, 0.0が画面の中心。
				{ 1.0f,0.0f,0.0f,1.0f },
				0.0f,
				0.8f/3.0f,
				{ 0.0f,1.0f }
			);
			break;
		}
	}
	if (MoveFlag == false) {
		switch (player_total)
		{
		case 1://1人。
			swprintf_s(moji, L"%d", (CountDownTime - time));		//表示用にデータを加工
			m_font.Draw(
				moji,		//表示する文字列。
				{ -150.0f,100.0f },			//表示する座標。0.0f, 0.0が画面の中心。
				{ 0.0f,0.0f,0.0f,1.0f },
				0.0f,
				1.5f,
				{ 0.0f,1.0f }
			);
			break;
		case 2://2人。
			swprintf_s(moji, L"%d", (CountDownTime - time));		//表示用にデータを加工
			m_font.Draw(
				moji,		//表示する文字列。
				{ -350.0f, 100.0f },			//表示する座標。0.0f, 0.0が画面の中心。
				{ 0.0f,0.0f,0.0f,1.0f },
				0.0f,
				1.5f/2.0,
				{ 0.0f,1.0f }
			);
			break;
		case 3:
		case 4:
			//3人以上。
			swprintf_s(moji, L"%d", (CountDownTime - time));		//表示用にデータを加工
			m_font.Draw(
				moji,		//表示する文字列。
				{ -350.0f,200.0f },			//表示する座標。0.0f, 0.0が画面の中心。
				{ 0.0f,0.0f,0.0f,1.0f },
				0.0f,
				1.5f/3.0f,
				{ 0.0f,1.0f }
			);
			break;
		}
	}
	if (m_time.GetSeconds() >= GameTime)
	{
		switch (player_total)
		{
		case 1://1人。
			swprintf_s(moji, L"そこまで");		//表示用にデータを加工
			m_font.Draw(
				moji,		//表示する文字列。
				{ -300.0f,100.0f },			//表示する座標。0.0f, 0.0が画面の中心。
				{ 1.0f,0.0f,0.0f,1.0f },
				0.0f,
				1.5f,
				{ 0.0f,1.0f }
			);
			break;
		case 2://2人。
			swprintf_s(moji, L"そこまで");		//表示用にデータを加工
			m_font.Draw(
				moji,		//表示する文字列。
				{ -450.0f,100.0f },			//表示する座標。0.0f, 0.0が画面の中心。
				{ 1.0f,0.0f,0.0f,1.0f },
				0.0f,
				1.5f/2.0f,
				{ 0.0f,1.0f }
			);
			break;
		case 3:
		case 4:
			//3人以上。
			swprintf_s(moji, L"そこまで");		//表示用にデータを加工
			m_font.Draw(
				moji,		//表示する文字列。
				{ -400.0f,200.0f },			//表示する座標。0.0f, 0.0が画面の中心。
				{ 1.0f,0.0f,0.0f,1.0f },
				0.0f,
				1.5f/3.0f,
				{ 0.0f,1.0f }
			);
			break;
		}
	}
	m_font.EndDraw();
	
}
