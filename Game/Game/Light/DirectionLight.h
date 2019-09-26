#pragma once
#include "Light.h"

namespace GameEngine {
	class DirectionLight : public IGameObject
	{
	public:
		DirectionLight();
		~DirectionLight();
		void Init();
		void UpdateSubResource();
		void SetDirection(const CVector3& dir) {
			m_light.direction = dir;
		}
		void SetColor(const CVector4& color) {
			m_light.color = color;
		}
	private:
		SDirectionLight m_light;
	};
};
