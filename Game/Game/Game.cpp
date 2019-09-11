#include "stdafx.h"
#include "Game.h"
#include "Player.h"

Game::Game()
{
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
}
