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
	m_titlebgm = NewGO<prefab::CSoundSource>(0);
	m_decisionse = NewGO<prefab::CSoundSource>(0);
	m_titlebgm->Init(L"Assets/sound/Title.wav");
	m_titlebgm->Play(true);
	m_titlebgm->SetVolume(0.5f);
	m_decisionse->Init(L"Assets/sound/battery1.wav");
	return true;
}

void Title::OnDestroy()
{
	DeleteGO(m_titlebgm);
	//DeleteGO(m_decisionse);
}

void Title::Update()
{

	if (g_pad[0].IsTrigger(enButtonA))
	{
		m_decisionse->Play(false);
		SceneChenge = true;

	}
	else if (SceneChenge&&m_decisionse->IsPlaying() == false)
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