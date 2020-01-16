#include "stdafx.h"
#include "GameSelect.h"
#include "Game.h"
#include "Light/DirectionLight.h"

GameSelect::GameSelect()
{
	//���C�g��z�u�B
	m_LigDirection = { 1.0f, -1.0f, 0.0f };
	m_LigDirection.Normalize();
	m_directionLight = NewGO<prefab::DirectionLight>(0, nullptr);
	m_directionLight->SetDirection(m_LigDirection);
	m_directionLight->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
}


GameSelect::~GameSelect()
{
}

bool GameSelect::Start()
{
	m_background.Init(L"Assets/sprite/selectback.dds", 1280.0f, 720.0f);
	m_tankmodel.Init(L"Assets/modelData/pz4_01.cmo");
	m_tankmodel2.Init(L"Assets/modelData/tiha.cmo");
	g_camera3D.SetPosition({ 0.0f,40.0f,100.0f });
	g_camera3D.SetTarget({0.0f,0.0f,0.0f});
	g_camera3D.SetFar(1000.0f);
	g_camera3D.Update();

	return true;
}

void GameSelect::Update()
{
	CQuaternion qrot;
	qrot.SetRotationDeg(CVector3::AxisY(), 2.0f);
	m_background.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_rotation.Multiply(qrot);
	m_tankmodel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_tankmodel2.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	switch (m_select)
	{
	case State_TankSelect:
		//���[���h�s��̍X�V�B
		if (g_pad[0].IsTrigger(enButtonA))
		{
			NewGO<Game>(0, "Game");
			DeleteGO(this);
		}
		if (g_pad[0].IsTrigger(enButtonRight))
		{
			m_select = State_TankSelect2;
		}
		break;
	case State_TankSelect2:
		if (g_pad[0].IsTrigger(enButtonA))
		{
			NewGO<Game>(0, "Game");
			DeleteGO(this);
		}
		if (g_pad[0].IsTrigger(enButtonRight))
		{
			m_select = State_TankSelect;
		}
		break;
	case State_PlayerSelect:
		if (g_pad[0].IsTrigger(enButtonUp))
		{
			m_playercount++;
		}
		if (g_pad[0].IsTrigger(enButtonA))
		{
			m_select = State_TankSelect;
		}
		break;
	}

}

void GameSelect::Draw()
{
	m_background.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);

}

void GameSelect::FontDraw()
{
	m_font.BeginDraw();
	switch (m_select)
	{
	case State_TankSelect:
		swprintf_s(m_moji, L"IV�����");		//�\���p�Ƀf�[�^�����H
		m_font.Draw(
		m_moji,		//�\�����镶����B
		{ -300.0f,-100.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
		{ 1.0f,0.0f,0.0f,1.0f },
		0.0f,
		m_mojisize,
		{ 0.0f,1.0f }
		);
		break;
	case State_TankSelect2:
		swprintf_s(m_moji, L"�㎵������ԃ`�n");		//�\���p�Ƀf�[�^�����H
		m_font.Draw(
			m_moji,		//�\�����镶����B
			{ -400.0f,-100.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
			{ 1.0f,0.0f,0.0f,1.0f },
			0.0f,
			m_mojisize,
			{ 0.0f,1.0f }
		);
		break;
	case State_PlayerSelect:
		swprintf_s(m_moji, L"�v���C�l��%d�l",m_playercount);		//�\���p�Ƀf�[�^�����H
		m_font.Draw(
			m_moji,		//�\�����镶����B
			{ -200.0f,0.0f },			//�\��������W�B0.0f, 0.0����ʂ̒��S�B
			{ 1.0f,0.0f,0.0f,1.0f },
			0.0f,
			0.8f,
			{ 0.0f,1.0f }
		);
		break;
	}
	if (m_select == State_TankSelect) {

	}
	if (m_select == State_TankSelect2) {

	}
	m_font.EndDraw();
}

void GameSelect::PostDraw()
{
	if (m_select == State_TankSelect) {
		m_tankmodel.Draw(
			enRenderMode_Normal,
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
	}
	if (m_select == State_TankSelect2) {
		m_tankmodel2.Draw(
			enRenderMode_Normal,
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
	}
	FontDraw();
}