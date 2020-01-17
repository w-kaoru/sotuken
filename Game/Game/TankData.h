#pragma once
#include "TankInfo.h"

class TankData:public IGameObject
{
public:
	TankData();
	~TankData();
	bool Start() override;
	void Select(TankType type);
	STankData* GetTankDeta() {
		return &m_data;
	}
private:
	STankData m_data;
	TankType m_type;
};

