#pragma once
#include "Define.h"
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

	/*
	*@brief �r���[�|�[�g��ݒ肷��֐�
	x		�������x���W
	y		�������y���W
	width	x����̉���
	height	y����̏c��
	Player* �J�����������Ă�v���C���[
	*/
	void SetViewPort(GameEngine::ViewPortParam param)
	{
		GameEngine::GetViewSplit().SetSplit(param);
		m_isViewport = true;
	}
	 //�r���[�|�[�g�𖢐ݒ�ɂ���B
	void FinishViewPort()
	{
		m_isViewport = false;
	}
	void SetPosition(CVector3 pos)
	{
		m_camera.SetPosition(pos);
		m_position = pos;
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
	/*void SetCameraPos(CVector3 pos)
	{
		m_position = pos;
	}*/
	void SetCameraTarget(CVector3 target)
	{
		m_target = target;
	}

	CVector3 GetForward()
	{
		return m_camera.GetForward();
	}
	CVector3 GetCameraPos() 
	{
		return m_camera.GetPosition();
	}
	bool Get_isViewport()
	{
		return m_isViewport;
	}
	//3D�J�������擾�B
	Camera& GetCamera()
	{
		return m_camera;
	}
	void SetNumber(int num) {
		m_number = num;
	}
private:
	Camera		m_camera;			//�J����
	CVector3    m_forword = CVector3::Zero();
	CVector3    m_target = CVector3::Zero();
	CVector3    m_position = CVector3::Zero();
	float       m_cameraSpeed = 0.02f;
	bool        m_aimFalg = false;
	bool	    m_isViewport = false;                   //�r���[�|�[�g���ݒ肳��Ă��邩�H
	int			m_number = 0;
};
//�Q�[���J�����̔z��B
extern GameCamera* g_gameCamera3D[PLAYER_NUM];      
//extern GameCamera* g_gameCamera2D[PLAYER_NUM];