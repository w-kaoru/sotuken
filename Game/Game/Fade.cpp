#include "stdafx.h"
#include "Fade.h"

Fade* g_fade;
Fade::Fade()
{

}


Fade::~Fade()
{
}

bool Fade::Start()
{
	//�t�F�[�h�p�̃f�[�^��ǂݍ���
	m_texture_fade.Init(L"Assets/sprite/White.dds", 1280.0f, 720.0f);
	m_texture_fade.SetclearColor(0.0f);
	return true;
}

void Fade::Update()
{
	m_texture_fade.SetclearColor(m_toumei);
	//��Ԃ̑J��
	switch (m_fadestate)
	{
	case fadein:
		m_toumei += m_faderate;
		if (m_toumei >= 1.1f)
		{
			m_toumei = 1.0f;
			m_fadestate = idel;
		}
		break;
	case fadeout:
		m_toumei += m_faderate;
		if (m_toumei <= 0.0f)
		{
			m_toumei = 0.0f;
			m_fadestate = idel;
		}
		break;
	case idel:
		break;
	default:
		break;
	}
}
void Fade::Draw()
{
	m_texture_fade.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
}