#include "stdafx.h"
#include "TankData.h"

TankData::TankData()
{
}

TankData::~TankData()
{
}

bool TankData::Start()
{
	return true;
}

void TankData::Select(TankType type)
{
	m_type = type;
	switch (type)
	{
	case pz4:
		m_data.hp = 100.0f;
		m_data.speed = 150.0f;
		m_data.bodyturn = 0.01f;
		m_data.cameraturn = 0.02f;
		break;
	case tiha:
		m_data.hp = 200.0f;//(‰¼)
		m_data.speed = 200.0f;//(‰¼)
		m_data.bodyturn = 200.0f;//(‰¼)
		m_data.cameraturn = 200.0f;//(‰¼)
		break;
	case nonType:
		return;
		break;
	}
}
