#include "stdafx.h"
#include "GameSelect.h"
#include "Game.h"
#include "Light/DirectionLight.h"
#include "TankData.h"
#include "StageData.h"

GameSelect::GameSelect()
{
	//ライトを配置。
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
	m_selectbgm = NewGO<prefab::CSoundSource>(0);
	m_cursorse = NewGO<prefab::CSoundSource>(0);
	m_decisionse = NewGO<prefab::CSoundSource>(0);
	m_taknData = NewGO<TankData>(0, "TankData");
	m_stagedata = NewGO<StageData>(0, "StageData");
	m_background.Init(L"Assets/sprite/selectback.dds", 1280.0f, 720.0f);
	m_tankmodel.Init(L"Assets/modelData/pz4.cmo");
	m_tankmodel2.Init(L"Assets/modelData/tiha.cmo");
	m_stagemodel.Init(L"Assets/modelData/CityMap1.cmo");
	m_stagemodel2.Init(L"Assets/modelData/GrassGround1.cmo");
	m_selectbgm->Init(L"Assets/sound/Select.wav");
	m_selectbgm->Play(true);
	m_selectbgm->SetVolume(0.5f);
	m_decisionse->Init(L"Assets/sound/battery1.wav");
	m_cursorse->Init(L"Assets/sound/cursor4.wav");
	m_cursorse->SetVolume(1.5f);
	g_camera3D.SetPosition({ 0.0f,40.0f,100.0f });
	g_camera3D.SetTarget({0.0f,0.0f,0.0f});
	g_camera3D.SetFar(1000.0f);
	g_camera3D.Update();
	 m_playernum =  max(min(4, m_playernum), 1);
	return true;
}

void GameSelect::OnDestroy()
{
	DeleteGO(m_selectbgm);
}
void GameSelect::Update()
{
	
	CQuaternion qrot;
	qrot.SetRotationDeg(CVector3::AxisY(), 2.0f);
	m_background.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_rotation.Multiply(qrot);
	m_tankmodel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_tankmodel2.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_stagemodel.UpdateWorldMatrix(CVector3::Zero(), m_rotation, m_stgaescale);
	m_stagemodel2.UpdateWorldMatrix(CVector3::Zero(), m_rotation, m_stgaescale);
	switch (m_gameselect)
	{
	case ninnzuu:

		if (g_pad[0].IsTrigger(enButtonUp))
		{
			m_playernum += 1;
		}
		if (g_pad[0].IsTrigger(enButtonDown))
		{
			m_playernum -= 1;
		}
		if (g_pad[0].IsTrigger(enButtonA))
		{
			m_gameselect = tank;
			m_select = pz4;
		}
		break;
	case tank:
		switch (m_select) {
		case pz4:
			if (g_pad[0].IsTrigger(enButtonA))
			{

				m_taknData->Select(m_select);
				m_gameselect = Stage1;
			}
			if (g_pad[0].IsTrigger(enButtonRight))
			{
				m_cursorse->Play(false);
				m_select = tiha;
			}
			break;
		case tiha:
			if (g_pad[0].IsTrigger(enButtonA))
			{

				m_taknData->Select(m_select);
				m_gameselect = Stage1;
			}
			if (g_pad[0].IsTrigger(enButtonRight))
			{
				m_cursorse->Play(false);
				m_select = pz4;
			}
			break;
		}
		break;
	case Stage1:
		if (g_pad[0].IsTrigger(enButtonRight))
		{
			m_gameselect = Stage2;
		}
		if (g_pad[0].IsTrigger(enButtonA))
		{
			m_decisionse->Play(false);
			deleteFlag = true;
		}
		break;
	case Stage2:
		if (g_pad[0].IsTrigger(enButtonRight))
		{
			m_gameselect = Stage1;
		}
		if (g_pad[0].IsTrigger(enButtonA))
		{
			m_decisionse->Play(false);
			deleteFlag = true;
		}
		break;
	}
	if (deleteFlag==true && m_decisionse->IsPlaying()== false) {

		m_taknData->Select(m_select);
		m_stagedata->Select(m_gameselect);
		Game* game = NewGO<Game>(0, "Game");
		//game->SetPlayer_Totle(m_playercount);
		game->SetPlayer_Totle(m_playernum);
		DeleteGO(this);
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
	switch (m_gameselect)
	{
	case ninnzuu:

		swprintf_s(m_moji, L"プレイ人数%d人",m_playernum);		//表示用にデータを加工
		m_font.Draw(
			m_moji,		//表示する文字列。
			{ -500.0f,-100.0f },			//表示する座標。0.0f, 0.0が画面の中心。
			{ 1.0f,0.0f,0.0f,1.0f },
			0.0f,
			m_mojisize,
			{ 0.0f,1.0f }
		);

		break;
	case tank:
		switch (m_select) {
		case pz4:
			swprintf_s(m_moji, L"IV号戦車");		//表示用にデータを加工
			m_font.Draw(
				m_moji,		//表示する文字列。
				{ -300.0f,-100.0f },			//表示する座標。0.0f, 0.0が画面の中心。
				{ 1.0f,0.0f,0.0f,1.0f },
				0.0f,
				m_mojisize,
				{ 0.0f,1.0f }
			);
			break;
		case tiha:
			swprintf_s(m_moji, L"九七式中戦車チハ");		//表示用にデータを加工
			m_font.Draw(
				m_moji,		//表示する文字列。
				{ -600.0f,-100.0f },			//表示する座標。0.0f, 0.0が画面の中心。
				{ 1.0f,0.0f,0.0f,1.0f },
				0.0f,
				m_mojisize,
				{ 0.0f,1.0f }
			);
			break;
		}
		break;
	case Stage1:

		break;
	case Stage2:
		break;
	}
	m_font.EndDraw();
}

void GameSelect::PostDraw()
{

	switch (m_gameselect)
	{
	case tank:
		switch (m_select) {
		case pz4:
			m_tankmodel.Draw(
				enRenderMode_Normal,
				g_camera3D.GetViewMatrix(),
				g_camera3D.GetProjectionMatrix()
			);
			break;
		case tiha:
			m_tankmodel2.Draw(
				enRenderMode_Normal,
				g_camera3D.GetViewMatrix(),
				g_camera3D.GetProjectionMatrix()
			);
			break;
		}
		break;
	case Stage1:
		m_stagemodel.Draw(
			enRenderMode_Normal,
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
		break;
	case Stage2:
		m_stagemodel2.Draw(
			enRenderMode_Normal,
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
		break;
	}
	FontDraw();
}