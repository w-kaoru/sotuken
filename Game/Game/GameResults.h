#pragma once
class Score;
class GameResults : public IGameObject
{
public:
	GameResults();
	~GameResults();
	bool Start();
	void OnDestroy()override;
	void Update();
	void Draw();
	void PostDraw();
	void SetScoreList(std::vector<Score*> list) {
		m_scoreList = list;
	}
private:
	std::vector<Score*> m_scoreList;
	wchar_t m_result[256];
	GameFont m_font;
	Sprite m_background;
	prefab::CSoundSource* m_resultbgm;
};

