#include "stdafx.h"
#include "DirectionLight.h"


namespace GameEngine {
	DirectionLight::DirectionLight()
	{
		m_light.color = CVector3::One();
		m_light.direction = CVector3::Down();
	}


	DirectionLight::~DirectionLight()
	{
	}
	void DirectionLight::Init()
	{
	}
	void DirectionLight::UpdateSubResource()
	{
	}
}