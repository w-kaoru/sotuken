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

	swprintf_s(m_result, L"�L�����@�@%d", (m_score->GetKillCount()));		//�\���p�Ƀf�[�^�����H
	m_font.Draw(
		m_result,		//�\�����镶����B
		{ -300.0f,100.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
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