#pragma once
class Score;
class GameResults : public IGameObject
{
public:
	GameResults();
	~GameResults();
	bool Start();
	void Update();
	void Draw();
	void PostDraw();
private:
	Score * m_score = nullptr;
	wchar_t m_result[256];
	GameFont m_font;
	Sprite m_background;
};

