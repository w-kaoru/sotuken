#include "stdafx.h"
#include "LightBase.h"

namespace GameEngine {
	namespace prefab {
		bool LightBase::Start()
		{
			return StartSub();
		}
		void LightBase::OnDestroy()
		{
			return OnDestroySub();
		}
	}
}