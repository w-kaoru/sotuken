#include "stdafx.h"
#include "UI.h"
#include "TankInfo.h"
#include "TankData.h"

UI::UI()
{
}

UI::~UI()
{
}

bool UI::Start()
{
	m_tankData = FindGO<TankData>("TankData");
	m_aiming.Init(L"Assets/sprite/aiming.dds", 100.0f, 100.0f);
	m_bulletsprite.Init(L"Assets/sprite/bullet.dds", 150.0f, 150.0f);
	m_playerhp.Init(L"Assets/sprite/hp_gauge.dds", 40.0f, 10.0f);
	return true;
}

void UI::Update()
{

	m_bulletsprite.Update({ -450.0f,-250.0f,0.0f }, CQuaternion::Identity(), CVector3::One());
	m_bulletsprite.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	switch (m_tankData->GetBulletType())
	{
	case HE:
		m_bulletsprite.SetColor({ 0.0f,0.0f,0.0f,1.0f });
		break;
	case AP:
		m_bulletsprite.SetColor({ 0.0f,1.0f,0.0f,1.0f });
		break;
	}
	m_aimingpos.y = -20.0f;
	m_aiming.Update(m_aimingpos, CQuaternion::Identity(), m_aimingScale);

	//HP�X�v���C�g�̍X�V
	m_playerhp.Update({ 400.0f,300.0f,0.0f }, CQuaternion::Identity(), { m_hp / 10.0f, 1.0f, 1.0f });
}

void UI::PostDraw()
{
	m_aiming.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	//HP�X�v���C�g�̕\��
	m_playerhp.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	m_bulletsprite.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
		);
	m_font.BeginDraw();
	switch (m_tankData->GetBulletType())
	{
	case HE:
		swprintf_s(m_moji, L"HE�e");		//�\���p�Ƀf�[�^�����H
		break;
	case AP:
		swprintf_s(m_moji, L"AP�e");		//�\���p�Ƀf�[�^�����H
		break;
	}
	m_font.Draw(
		m_moji,		//�\�����镶����B
		{ -500.0f,-200.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
		{ 1.0f,0.0f,0.0f,1.0f },
		0.0f,
		0.8f,
		{ 0.0f,1.0f }
	);
	m_font.EndDraw();
}
