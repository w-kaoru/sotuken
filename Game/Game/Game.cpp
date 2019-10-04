#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "TestEnemy.h"
#include "BulletManeger.h"
#include "BackGround.h"
#include "GameCamera.h"

Game::Game()
{
	m_testbgm.Init(L"Assets/sound/coinGet.wav");
	//m_testbgm.Play(true);
	m_testEffect = Effekseer::Effect::Create(g_graphicsEngine->GetEffekseerManager(),
		(const EFK_CHAR*)L"Assets/effect/test.efk");
}


Game::~Game()
{
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

void Game::Update()
{
	//if (g_pad[0].IsTrigger(enButtonA))
	//{
	//	DeleteGO(m_player);
	//}
	if (g_pad[0].IsTrigger(enButtonB))
	{
		//エフェクトを再生する。
		m_testEffectHandle = g_graphicsEngine->GetEffekseerManager()->Play(
			m_testEffect,
			0.0f, 0.0f,0.0f);
		//エフェクトの大きさを変更
		g_graphicsEngine->GetEffekseerManager()->SetScale(
			m_testEffectHandle, 
			20.0f,
			20.0f,
			20.0f);
	}
}

void Game::Draw()
{

}
