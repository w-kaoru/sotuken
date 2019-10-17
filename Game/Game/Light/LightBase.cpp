#include "stdafx.h"
#include "LightBase.h"

namespace GameEngine {
	namespace prefab {
		bool LightBase::Start()
		{
			g_graphicsEngine->GetLightManager()->AddLight(this);
			return StartSub();
		}
		void LightBase::OnDestroy()
		{
			g_graphicsEngine->GetLightManager()->RemoveLight(this);
			return OnDestroySub();
		}
	}
}