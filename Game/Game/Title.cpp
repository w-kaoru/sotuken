#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "GameSelect.h"
Title::Title()
{
}


Title::~Title()
{

}

bool Title::Start()
{
	m_sprite.Init(L"Assets/sprite/Title1.dds", 1280.0f, 720.0f);
	return true;
}

void Title::Update()
{
	if (g_pad[0].IsTrigger(enButtonA))
	{
		NewGO<GameSelect>(0, "GameSelect");
		DeleteGO(this);
	}
	m_sprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
}

void Title::PostDraw()
{
	m_sprite.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
}