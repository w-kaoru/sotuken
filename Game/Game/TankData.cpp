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
		m_data.defense = 60.0f;
		m_data.m_reload = 60.0f;
		m_data.scale = 0.5f;
		m_data.BOXLength = { 60.0f, 100.0f, 100.0f };
		break;
	case tiha:
		m_data.filePath_00 = L"Assets/modelData/tiha_body.cmo";
		m_data.filePath_01 = L"Assets/modelData/tiha_houtou.cmo";
		m_data.hp = 100.0f;//(‰¼)
		m_data.speed = 150.0f;//(‰¼)
		m_data.bodyturn = 0.02f;//(‰¼)
		m_data.cameraturn = 0.02f;//(‰¼)
		m_data.defense = 40.0f;
		m_data.m_reload = 30.0f;
		m_data.scale = 0.3f;
		m_data.BOXLength = { 60.0f, 100.0f, 100.0f };//(‰¼)
		break;
	}
}