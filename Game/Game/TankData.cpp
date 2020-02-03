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
		m_data.scale = 0.5f;
		m_data.BOXLength = { 60.0f, 100.0f, 100.0f };
		break;
	case tiha:
		m_data.filePath_00 = L"Assets/modelData/tiha_body.cmo";
		m_data.filePath_01 = L"Assets/modelData/tiha_houtou.cmo";
		m_data.hp = 220.0f;//(‰¼)
		m_data.speed = 150.0f;//(‰¼)
		m_data.bodyturn = 0.02f;//(‰¼)
		m_data.cameraturn = 0.02f;//(‰¼)
		m_data.defense = 40.0f;
		m_data.scale = 0.3f;
		m_data.BOXLength = { 60.0f, 100.0f, 100.0f };//(‰¼)
		break;
	case nonType:
		return;
		break;
	}
}

void TankData::BulletSelect(BulletType btype)
{
	m_bullettype = btype;
	switch (btype)
	{
	case HE:
		m_data.bulletdamage = 100.0f;
		m_data.bulletSpeed = 5000.0f;
		break;
	case AP:
		m_data.bulletdamage = 150.0f;
		m_data.bulletSpeed = 10000.0f;
		break;
	case num:
		return;
		break;
	}

}

