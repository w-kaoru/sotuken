#pragma once
class Player;
class Score:public IGameObject
{
public:
	Score();
	~Score();
	bool Start();
	void Update();
	void Draw();
	void KillPlus()
	{
		m_killCount += 1;
	}

	void DethPlus()
	{
		m_dethCount += 1;
	}
	int GetKillCount()
	{
		return m_killCount;
	}
	int GetDethCount()
	{
		return m_dethCount;
	}
private:
	int m_killCount = 0;
	int m_dethCount = 0;
};

