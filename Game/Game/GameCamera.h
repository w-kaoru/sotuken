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
private:
	Player* m_player = nullptr;

};

