#include "stdafx.h"
#include "Game.h"
#include "Player.h"

Game::Game()
{
	m_testbgm.Init(L"Assets/sound/coinGet.wav");
	m_testbgm.Play(true);
}


Game::~Game()
{
}

bool Game::Start()
{
	m_player = NewGO<Player>(1, "Player");
	return true;
}

void Game::Update()
{
	if (g_pad[0].IsTrigger(enButtonA))
	{
		//DeleteGO("Player");
		DeleteGO(m_player);
	}
}

void Game::Draw()
{
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
