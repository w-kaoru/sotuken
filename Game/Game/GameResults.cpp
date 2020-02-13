#include "stdafx.h"
#include "GameResults.h"
#include "Score.h"
#include "Title.h"

GameResults::GameResults()
{
}


GameResults::~GameResults()
{
}

bool GameResults::Start()
{
	m_background.Init(L"Assets/sprite/ResultBack.dds", 1280.0f, 720.0f);
	m_resultbgm = NewGO<prefab::CSoundSource>(0);
	m_resultbgm->Init(L"Assets/sound/result.wav");
	m_resultbgm->Play(true);
	return true;
}

void GameResults::OnDestroy()
{
	DeleteGO(m_resultbgm);

	for (auto score : m_scoreList) {
		if (score != nullptr) {
			DeleteGO(score);
		}
	}
	for (auto score : m_scoreList) {
		if (!score) {
			m_scoreList.erase(std::remove(m_scoreList.begin(), m_scoreList.end(), score), m_scoreList.end());
		}
	}
}

void GameResults::Update()
{
	m_background.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	if (g_pad[0].IsTrigger(enButtonA)) {
		NewGO<Title>(1, "title");
		DeleteGO(this);
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
	int num = 1;
	float posY = 300.0f;
	for (auto score : m_scoreList) {
		swprintf_s(m_result, L"Player_%d: Kill  %d  Deth  %d", num, (score->GetKillCount()), (score->GetDethCount()));		//表示用にデータを加工
		m_font.Draw(
			m_result,		//表示する文字列。
			{ -540.0f,posY },			//表示する座標。0.0f, 0.0が画面の中心。
			{ 1.0f,0.0f,0.0f,1.0f },
			0.0f,
			0.8f,
			{ 0.0f,1.0f }
		);
		num++;
		posY -= 150.0f;
	}
	/*swprintf_s(m_result, L"Player2\nKill　　%d  Deth   %d", (m_score->GetKillCount2()), (m_score->GetDethCount2()));		//表示用にデータを加工
	m_font.Draw(
		m_result,		//表示する文字列。
		{ -400.0f,0.0f },			//表示する座標。0.0f, 0.0が画面の中心。
		{ 1.0f,0.0f,0.0f,1.0f },
		0.0f,
		0.8f,
		{ 0.0f,1.0f }
	);*/
	m_font.EndDraw();
}