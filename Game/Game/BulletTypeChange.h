#pragma once
#include "TankInfo.h"
#include "TankData.h"

class BulletTypeChange : public IGameObject
{
public:
	BulletTypeChange();
	~BulletTypeChange();
	void BulletSelect(BulletType btype);
	BulletType GetBulletType()
	{
		return m_bullettype;
	}
	STankBulletInfo* GetTankBulletInfo() {
		return &m_data;
	}
	//BulletSelectÇÊÇËêÊÇ…åƒÇÒÇ≈ÇÀÅB
	void SetTankType(TankType type) {
		m_tankType = type;
	}
private:
	BulletType m_bullettype;
	STankBulletInfo m_data;
	TankType m_tankType = TankType::nonType;
};


