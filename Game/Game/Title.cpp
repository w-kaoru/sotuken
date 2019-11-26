#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title()
{
}


Title::~Title()
{

}

bool Title::Start()
{
	m_sprite.Init(L"Assets/sprite/title.dds", 1280.0f, 720.0f);

	return true;
}

void Title::Update()
{
	m_sprite.Update({ 0.0f,0.0f,0.0f }, CQuaternion::Identity(), CVector3::One());
	if (g_pad[0].IsTrigger(enButtonA))
	{
		NewGO<Game>(0, "Game");
		DeleteGO(this);
	}
}

void Title::Draw()
{
	m_sprite.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
}