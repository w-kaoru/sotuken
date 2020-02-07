#pragma once
#include "stdafx.h"
#include "ViewPortSplit/ViewPortSplit.h"
#include "GameObject/IGameObject.h"
class UI;
class GameCamera : public GameEngine::IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start()override;
	void Update()override;

	CVector3 GetCameraPos() 
	{
		return m_camera.GetPosition();
	}
	void SetCameraPos(CVector3 pos)
	{
		m_position = pos;
		m_camera.SetPosition(pos);
	}

	/*
	*@brief ビューポートを設定する関数
	x		左上隅のx座標
	y		左上隅のy座標
	width	xからの横幅
	height	yからの縦幅
	Player* カメラを持ってるプレイヤー
	*/
	void SetViewPort(GameEngine::ViewPortParam param)
	{
		GameEngine::GetViewSplit().SetSplit(param);
		m_isViewport = true;
	}
	 //ビューポートを未設定にする。
	void FinishViewPort()
	{
		m_isViewport = false;
	}
	void SetPosition(CVector3 pos)
	{
		m_camera.SetPosition(pos);
	}
	void SetAimFlag(bool flag)
	{
		m_aimFalg = flag;
	}
	void SetTarget(CVector3 target)
	{
		m_target = target;
		m_camera.SetTarget(target);
	}
	void SetCameraSpeed(float speed)
	{
		m_cameraSpeed = speed;
	}

	bool Get_isViewport()
	{
		return m_isViewport;
	}
	//3Dカメラを取得。
	Camera& GetCamera()
	{
		return m_camera;
	}
	void SetNumber(int num) {
		m_number = num;
	}
private:
	Camera		m_camera;			//カメラ
	CVector3    m_forword = CVector3::Zero();
	CVector3    m_target = CVector3::Zero();
	CVector3    m_position = CVector3::Zero();
	float       m_cameraSpeed = 0.02f;
	bool        m_aimFalg = false;
	bool	    m_isViewport;                   //ビューポートが設定されているか？
	int			m_number = 0;
};
//ゲームカメラの配列。
extern GameCamera* g_gameCamera3D[4];      
//extern GameCamera* g_gameCamera2D[PLAYER_NUM];