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
		m_data.filePath_00 = L"Assets/modelData/pz4_00.cmo";
		m_data.filePath_01 = L"Assets/modelData/pz4_01.cmo";
		m_data.hp = 100.0f;
		m_data.speed = 150.0f;
		m_data.bodyturn = 0.012f;
		m_data.cameraturn = 0.02f;
		break;
	case tiha:
		m_data.filePath_00 = L"Assets/modelData/tiha_body.cmo";
		m_data.filePath_01 = L"Assets/modelData/tiha_houtou.cmo";
		m_data.hp = 200.0f;//(‰¼)
		m_data.speed = 200.0f;//(‰¼)
		m_data.bodyturn = 0.012f;//(‰¼)
		m_data.cameraturn = 0.02f;//(‰¼)
		break;
	case nonType:
		return;
		break;
	}
}
