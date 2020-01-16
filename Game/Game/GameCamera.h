#pragma once
class Player;
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	void SetPlayer(Player* player)
	{
		m_player = player;
	}
	CVector3 GetCameraPos() 
	{
		return g_camera3D.GetPosition();
	}
private:
	Player* m_player = nullptr;
	CVector3 m_forword = CVector3::Zero();
};

