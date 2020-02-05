#include "stdafx.h"
#include "system/system.h"
#include "Game.h"
#include "Title.h"
///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	g_camera2D.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
	g_camera2D.SetWidth(FRAME_BUFFER_W);
	g_camera2D.SetHeight(FRAME_BUFFER_H);
	g_camera2D.SetPosition({ 0.0f, 0.0f, -10.0f });
	g_camera2D.SetTarget(CVector3::Zero());
	g_camera2D.Update();
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	GOManager().Init(50);
	//CSoundEngine soundEngine;				//�T�E���h�G���W���B
	SoundEngine().Init();
	g_physics.SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
	NewGO<Title>(0, "Title");

	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//�Q�[���I�u�W�F�N�g�̍X�V�B
		GOManager().Execute();
		//�T�E���h�G���W���̍X�V
		SoundEngine().Update();
		//�����G���W���̍X�V�B
		g_physics.Update();
		//�`��I���B
		g_graphicsEngine->EndRender();
	}
}