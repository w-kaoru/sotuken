#pragma once
#include "TankInfo.h"
class StageData:public IGameObject
{
public:
	StageData();
	~StageData();
	bool Start() override;
	void Select(Stagenum type);
	SSelectInfo* GetStageDeta() {
		return &m_data;
	}
	Stagenum GetStageType()
	{
		return m_type;
	}
private:
	SSelectInfo m_data;
	Stagenum m_type;
};

