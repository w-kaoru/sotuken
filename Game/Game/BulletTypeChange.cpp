#include "stdafx.h"
#include "BulletTypeChange.h"

BulletTypeChange::BulletTypeChange()
{
}

BulletTypeChange::~BulletTypeChange()
{
}

void BulletTypeChange::BulletSelect(BulletType btype)
{
	m_bullettype = btype;
	switch (m_tankType)
	{
	case pz4:
		switch (btype)
		{
		case HE:
			m_data.bulletdamage = 200.0f;
			m_data.bulletSpeed = 500.0f * 10.0f;
			break;
		case AP:
			m_data.bulletdamage = 100.0f;
			m_data.bulletSpeed = 1000.0f * 10.0f;
			break;
		case num:
			return;
			break;
		}
		break;
	case tiha:
		switch (btype)
		{
		case HE:
			m_data.bulletdamage = 200.0f;
			m_data.bulletSpeed = 500.0f * 10.0f;
			break;
		case AP:
			m_data.bulletdamage = 100.0f;
			m_data.bulletSpeed = 1000.0f * 10.0f;
			break;
		case num:
			return;
			break;
		}
		break;
	}

}