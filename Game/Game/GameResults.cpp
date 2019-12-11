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
	m_background.Init(L"Assets/sprite/ResultBack.dds", 1280.0f, 720.0f);
	m_score = FindGO<Score>("Score");
	return true;
}

void GameResults::Update()
{
	m_background.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	if (g_pad[0].IsTrigger(enButtonA)) {
		DeleteGO(this);
		NewGO<Title>(1, "title");
	}
}

void GameResults::Draw()
{
	m_background.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);

}

void GameResults::PostDraw()
{
	m_font.BeginDraw();

	swprintf_s(m_result, L"Player1\nKill　　%d  Deth   %d", (m_score->GetKillCount()),(m_score->GetDethCount()));		//表示用にデータを加工
	m_font.Draw(
		m_result,		//表示する文字列。
		{ -400.0f,300.0f },			//表示する座標。0.0f, 0.0が画面の中心。
		{ 0.0f,0.0f,0.0f,1.0f },
		0.0f,
		0.8f,
		{ 0.0f,1.0f }
	);
	swprintf_s(m_result, L"Player2\nKill　　%d  Deth   %d", (m_score->GetKillCount2()), (m_score->GetDethCount2()));		//表示用にデータを加工
	m_font.Draw(
		m_result,		//表示する文字列。
		{ -400.0f,0.0f },			//表示する座標。0.0f, 0.0が画面の中心。
		{ 0.0f,0.0f,0.0f,1.0f },
		0.0f,
		0.8f,
		{ 0.0f,1.0f }
	);
	m_font.EndDraw();
}