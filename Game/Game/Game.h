#pragma once
class Player;
class Game:public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Draw();
private:
	Player* m_player = nullptr;
};

