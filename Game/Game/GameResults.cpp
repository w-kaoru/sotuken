#include "stdafx.h"
#include "GameResults.h"
#include "Score.h"
#include "Title.h"

GameResults::GameResults()
{
}


GameResults::~GameResults()
{
	DeleteGO(m_score);
}

bool GameResults::Start()
{
	m_score = FindGO<Score>("Score");
	return true;
}

void GameResults::Update()
{
	if (g_pad[0].IsTrigger(enButtonA)) {
		DeleteGO(this);
		NewGO<Title>(1, "title");
	}
}

void GameResults::Draw()
{
	m_font.BeginDraw();

	swprintf_s(m_result, L"キル数　　%d", (m_score->GetKillCount()));		//表示用にデータを加工
	m_font.Draw(
		m_result,		//表示する文字列。
		{ -300.0f,100.0f },			//表示する座標。0.0f, 0.0が画面の中心。
		{ 0.0f,0.0f,1.0f,1.0f },
		0.0f,
		0.8f,
		{ 0.0f,1.0f }
	);
	

	m_font.EndDraw();

}

void GameResults::PostDraw()
{

}