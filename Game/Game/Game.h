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
	wchar_t moji[256];
	GameFont m_font;
	float m_fontsize = 1.0f; //�t�H���g�T�C�Y
	CSoundSource m_testbgm;
};

