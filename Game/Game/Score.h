#pragma once
class Player;
class TestEnemy;
class Score:public IGameObject
{
public:
	Score();
	~Score();
	bool Start();
	void Update();
	void Draw();
	void ScorePlus()
	{
		m_playerkillcount += 1;
		m_playerdethcount2 += 1;
	}

	void DethPlus()
	{
		m_playerdethcount += 1;
		m_playerkillcount2 += 1;
	}
	int GetKillCount()
	{
		return m_playerkillcount;
	}
	int GetDethCount()
	{
		return m_playerdethcount;
	}
	int GetKillCount2()
	{
		return m_playerkillcount2;
	}
	int GetDethCount2()
	{
		return m_playerdethcount2;
	}
private:
	int m_playerkillcount = 0;
	int m_playerdethcount = 0;
	int m_playerkillcount2 = 0;
	int m_playerdethcount2= 0;
	wchar_t score[256];
	wchar_t deth[256];
	GameFont m_font;
	Player* m_player = nullptr;
	TestEnemy* m_enemy = nullptr;
};

