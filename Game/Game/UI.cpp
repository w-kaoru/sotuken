#include "stdafx.h"
#include "UI.h"
#include "TankInfo.h"
#include "TankData.h"
#include "BulletTypeChange.h"
#include "Game.h"

UI::UI()
{
}

UI::~UI()
{
}

bool UI::Start()
{
	//m_tankData = FindGO<TankData>("TankData");
	m_aiming.Init(L"Assets/sprite/aiming.dds", 100.0f, 100.0f);
	m_bulletsprite.Init(L"Assets/sprite/bullet.dds", 150.0f, 150.0f);
	m_playerhp.Init(L"Assets/sprite/hp_gauge.dds", 40.0f, 10.0f);
	player_total = FindGO<Game>("Game")->Get_Player_Totle();
	return true;
}

void UI::Update()
{

	m_bulletsprite.Update({ -450.0f,-250.0f,0.0f }, CQuaternion::Identity(), CVector3::One());
	m_bulletsprite.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	switch (m_bulletChange->GetBulletType())
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

	//HPスプライトの更新
	m_playerhp.Update({ 600.0f,300.0f,0.0f }, CQuaternion::Identity(), { m_hp / 10.0f, 1.0f, 1.0f }, {1.0f,0.5f});
}

void UI::PostDraw()
{
	m_aiming.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	//HPスプライトの表示
	m_playerhp.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	m_bulletsprite.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	m_font.BeginDraw();
	switch (m_bulletChange->GetBulletType())
	{
	case HE:
		swprintf_s(m_moji, L"HE弾");		//表示用にデータを加工
		break;
	case AP:
		swprintf_s(m_moji, L"AP弾");		//表示用にデータを加工
		break;
	}
	m_font.Draw(
		m_moji,		//表示する文字列。
		{ -500.0f,-200.0f },			//表示する座標。0.0f, 0.0が画面の中心。
		{ 1.0f,0.0f,0.0f,1.0f },
		0.0f,
		m_fontsize,
		{ 0.0f,1.0f }
	);
	m_font.EndDraw();
}

void UI::PostDraw(int player_num)
{
	//現在の描画対象プレイヤーと一致すれば描画する。
	if (player_num== m_number) {
		m_aiming.Draw(
			g_camera2D.GetViewMatrix(),
			g_camera2D.GetProjectionMatrix()
		);
		//HPスプライトの表示
		m_playerhp.Draw(
			g_camera2D.GetViewMatrix(),
			g_camera2D.GetProjectionMatrix()
		);
		m_bulletsprite.Draw(
			g_camera2D.GetViewMatrix(),
			g_camera2D.GetProjectionMatrix()
		);
		m_font.BeginDraw();
		switch (m_bulletChange->GetBulletType())
		{
		case HE:
			swprintf_s(m_moji, L"HE弾");		//表示用にデータを加工
			break;
		case AP:
			swprintf_s(m_moji, L"AP弾");		//表示用にデータを加工
			break;
		}
		switch (player_total)
		{
		case 1://1人。
			m_font.Draw(
				m_moji,		//表示する文字列。
				{ -500.0f,-200.0f },			//表示する座標。0.0f, 0.0が画面の中心。
				{ 1.0f,0.0f,0.0f,1.0f },
				0.0f,
				m_fontsize,
				{ 0.0f,1.0f }
			);
			break;
		case 2://2人。
			m_font.Draw(
				m_moji,		//表示する文字列。
				{ -600.0f,-200.0f },			//表示する座標。0.0f, 0.0が画面の中心。
				{ 1.0f,0.0f,0.0f,1.0f },
				0.0f,
				m_fontsize,
				{ 0.0f,1.0f }
			);
			break;
		case 3:
		case 4:
			//3人以上。
			m_font.Draw(
				m_moji,		//表示する文字列。
				{ -570.0f,80.0f },			//表示する座標。0.0f, 0.0が画面の中心。
				{ 1.0f,0.0f,0.0f,1.0f },
				0.0f,
				m_fontsize/2.0f,
				{ 0.0f,1.0f }
			);
			break;
		}
		m_font.EndDraw();
	}
}
