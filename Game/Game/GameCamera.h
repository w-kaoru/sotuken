#pragma once
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	CVector3 GetCameraPos() 
	{
		return g_camera3D.GetPosition();
	}
	void SetCameraPos(CVector3 pos)
	{
		m_position = pos;
	}
	void SetPosition(CVector3 pos)
	{
		g_camera3D.SetPosition(pos);
	}
	void SetAimFlag(bool flag)
	{
		m_aimFalg = flag;
	}
	void SetTarget(CVector3 target)
	{
		m_target = target;
	}
	void SetCameraSpeed(float speed)
	{
		m_cameraSpeed = speed;
	}
private:
	CVector3 m_forword = CVector3::Zero();
	CVector3 m_target = CVector3::Zero();
	CVector3 m_position = CVector3::Zero();
	float m_cameraSpeed = 0.0f;
	bool m_aimFalg = false;
};

