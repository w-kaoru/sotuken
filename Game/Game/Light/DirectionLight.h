#pragma once
#include "Light.h"
#include "LightBase.h"

namespace GameEngine {
	namespace prefab {
		class DirectionLight : public LightBase
		{
		public:
			DirectionLight();
			~DirectionLight();
			bool StartSub() override final;
			void Update() override final;
			void SetDirection(const CVector3& dir) {
				m_light.direction = dir;
			}
			void SetColor(const CVector4& color) {
				m_light.color = color;
			}
			//生データの取得。
			SDirectionLight& GetRawData()
			{
				return m_light;
			}
		private:
			SDirectionLight m_light;
		};
	};
};
