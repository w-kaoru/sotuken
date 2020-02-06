#include "stdafx.h"
#include "GameSelect.h"
#include "Game.h"
#include "Light/DirectionLight.h"
#include "TankData.h"

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
	m_background.Init(L"Assets/sprite/selectback.dds", 1280.0f, 720.0f);
	m_tankmodel.Init(L"Assets/modelData/pz4.cmo");
	m_tankmodel2.Init(L"Assets/modelData/tiha.cmo");
	g_camera3D.SetPosition({ 0.0f,40.0f,100.0f });
	g_camera3D.SetTarget({0.0f,0.0f,0.0f});
	g_camera3D.SetFar(1000.0f);
	g_camera3D.Update();

	return true;
}

void GameSelect::Update()
{
	bool deleteFlag = false;
	CQuaternion qrot;
	qrot.SetRotationDeg(CVector3::AxisY(), 2.0f);
	m_background.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_rotation.Multiply(qrot);
	m_tankmodel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_tankmodel2.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	switch (m_select)
	{
	case pz4:
		//ワールド行列の更新。
		if (g_pad[0].IsTrigger(enButtonA))
		{
			deleteFlag = true;
		}
		if (g_pad[0].IsTrigger(enButtonRight))
		{
			m_select = tiha;
		}
		break;
	case tiha:
		if (g_pad[0].IsTrigger(enButtonA))
		{
			deleteFlag = true;
		}
		if (g_pad[0].IsTrigger(enButtonRight))
		{
			m_select = pz4;
		}
		break;
	case nonType:
		if (g_pad[0].IsTrigger(enButtonUp))
		{
			m_playercount++;
		}
		if (g_pad[0].IsTrigger(enButtonA))
		{
			m_select = pz4;
		}
		break;
	}
	if (deleteFlag) {
		m_taknData = NewGO<TankData>(0, "TankData");
		m_taknData->Select(m_select);
		Game* game = NewGO<Game>(0, "Game");
		game->SetPlayer_Totle(m_playercount);
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
	switch (m_select)
	{
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
	case nonType:
		swprintf_s(m_moji, L"プレイ人数%d人",m_playercount);		//表示用にデータを加工
		m_font.Draw(
			m_moji,		//表示する文字列。
			{ -200.0f,0.0f },			//表示する座標。0.0f, 0.0が画面の中心。
			{ 1.0f,0.0f,0.0f,1.0f },
			0.0f,
			0.8f,
			{ 0.0f,1.0f }
		);
		break;
	}
	m_font.EndDraw();
}

void GameSelect::PostDraw()
{
	if (m_select == pz4) {
		m_tankmodel.Draw(
			enRenderMode_Normal,
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
	}
	if (m_select == tiha) {
		m_tankmodel2.Draw(
			enRenderMode_Normal,
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
	}
	FontDraw();
}