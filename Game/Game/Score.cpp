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
	//swprintf_s(score, L"�L����%02d", (m_playerkillcount));		//�\���p�Ƀf�[�^�����H
	//m_font.Draw(
	//	score,		//�\�����镶����B
	//	{ -620.0f,-150.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
	//	{ 1.0f,0.0f,0.0f,1.0f },
	//	0.0f,
	//	0.6f,
	//	{ 0.0f,1.0f }
	//);
	//swprintf_s(deth, L"�f�X��%02d", (m_playerdethcount));		//�\���p�Ƀf�[�^�����H
	//m_font.Draw(
	//	deth,		//�\�����镶����B
	//	{ -620.0f,-250.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
	//	{ 1.0f,0.0f,0.0f,1.0f },
	//	0.0f,
	//	0.6f,
	//	{ 0.0f,1.0f }
	//);
	//m_font.EndDraw();
}