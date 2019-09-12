#include "stdafx.h"
#include "Game.h"
#include "Player.h"

Game::Game()
{
	m_testbgm.Init(L"Assets/sound/coinGet.wav");
	m_testbgm.Play(true);
	m_testEffect = Effekseer::Effect::Create(g_graphicsEngine->GetEffekseerManager(),
		(const EFK_CHAR*)L"Assets/effect/test.efk");
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
	if (g_pad[0].IsTrigger(enButtonB))
	{
		//�G�t�F�N�g���Đ�����B
		m_testEffectHandle = g_graphicsEngine->GetEffekseerManager()->Play(
			m_testEffect,
			0.0f, 0.0f,0.0f);
		//�G�t�F�N�g�̑傫����ύX
		g_graphicsEngine->GetEffekseerManager()->SetScale(
			m_testEffectHandle, 
			20.0f,
			20.0f,
			20.0f);
	}
}

void Game::Draw()
{
	m_font.BeginDraw();
	swprintf_s(moji, L"HELLO");
	m_font.Draw
	(
		moji,		//�\�����镶����B
		{ -100.0f,FRAME_BUFFER_H / 2.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
		{ 1.0f,0.0f,0.0f,1.0f },
		0.0f,
		m_fontsize,
		{ 0.0f,1.0f }
	);
	m_font.EndDraw();
}
