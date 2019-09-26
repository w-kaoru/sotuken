#include "stdafx.h"
#include "system/system.h"
#include "Game.h"

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	g_camera2D.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
	g_camera2D.SetWidth(FRAME_BUFFER_W);
	g_camera2D.SetHeight(FRAME_BUFFER_H);
	g_camera2D.SetPosition({ 0.0f, 0.0f, -10.0f });
	g_camera2D.SetTarget(CVector3::Zero());
	g_camera2D.Update();
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	GOManager().Init(50);
	CSoundEngine soundEngine;				//サウンドエンジン。
	soundEngine.Init(); 
	NewGO<Game>(0, "Game");

	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//描画開始。
		g_graphicsEngine->BegineRender();
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//ゲームオブジェクトの更新。
		GOManager().Execute();
		//サウンドエンジンの更新
		soundEngine.Update();
		//物理エンジンの更新。
		g_physics.Update();
		//エフェクトの更新
		g_graphicsEngine->EffectUpdate();
		//描画終了。
		g_graphicsEngine->EndRender();
	}
}