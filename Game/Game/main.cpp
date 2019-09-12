#include "stdafx.h"
#include "system/system.h"
#include "Game.h"

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);

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
		//カメラの更新。
		g_camera3D.Update();
		//描画終了。
		g_graphicsEngine->EndRender();
	}
}