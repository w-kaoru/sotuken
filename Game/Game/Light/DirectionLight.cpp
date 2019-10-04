#include "stdafx.h"
#include "DirectionLight.h"


namespace GameEngine {
	namespace prefab {
		DirectionLight::DirectionLight()
		{
			m_light.color = CVector3::One();
			m_light.direction = CVector3::Down();
		}


		DirectionLight::~DirectionLight()
		{
		}
		bool DirectionLight::StartSub()
		{
			return false;
		}
		void DirectionLight::Update()
		{
		}
		void DirectionLight::UpdateSubResource()
		{
		}
	}
}