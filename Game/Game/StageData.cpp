#include "stdafx.h"
#include "StageData.h"

StageData::StageData()
{
}

StageData::~StageData()
{
}

bool StageData::Start()
{
	return true;
}

void StageData::Select(Stagenum type)
{
	m_type = type;
	switch (type)
	{
	case Stage1:
		m_data.filePath = L"Assets/modelData/CityMap1.cmo";
		m_data.position = CVector3::Zero();
		m_data.rotation = CQuaternion::Identity();
		m_data.scale = CVector3::One();
		break;
	case Stage2:
		m_data.filePath = L"Assets/modelData/GrassGround1.cmo";
		m_data.position = CVector3::Zero();
		m_data.rotation = CQuaternion::Identity();
		m_data.scale = CVector3::One();
		break;
	}
}
