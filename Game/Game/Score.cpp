#include "stdafx.h"
#include "Score.h"
#include "Player.h"
#include "TestEnemy.h"

Score::Score()
{
}


Score::~Score()
{
}

bool Score::Start()
{
	m_player = FindGO<Player>("Player");
	m_enemy = FindGO<TestEnemy>("TestEnemy");
	return true;
}

void Score::Update()
{

}

void Score::Draw()
{
	//m_font.BeginDraw();
	//swprintf_s(score, L"キル数%02d", (m_playerkillcount));		//表示用にデータを加工
	//m_font.Draw(
	//	score,		//表示する文字列。
	//	{ -620.0f,-150.0f },			//表示する座標。0.0f, 0.0が画面の中心。
	//	{ 1.0f,0.0f,0.0f,1.0f },
	//	0.0f,
	//	0.6f,
	//	{ 0.0f,1.0f }
	//);
	//swprintf_s(deth, L"デス数%02d", (m_playerdethcount));		//表示用にデータを加工
	//m_font.Draw(
	//	deth,		//表示する文字列。
	//	{ -620.0f,-250.0f },			//表示する座標。0.0f, 0.0が画面の中心。
	//	{ 1.0f,0.0f,0.0f,1.0f },
	//	0.0f,
	//	0.6f,
	//	{ 0.0f,1.0f }
	//);
	//m_font.EndDraw();
}