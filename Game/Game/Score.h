#pragma once
#include "stdafx.h"
#include "Score.h"
class Score:public IGameObject
{
public:
	Score() {};
	~Score() {};
	bool Start() { return false; };
	void Update() {};
	void Draw() {};
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
	void SetName(char* name) {
		m_name = name;
	}
	char* GetName() {
		return m_name;
	}
private:
	int m_killCount = 0;
	int m_dethCount = 0;
	char* m_name = nullptr;
};

