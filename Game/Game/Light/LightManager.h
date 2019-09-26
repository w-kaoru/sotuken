#pragma once
#include "LightBase.h"
namespace GameEngine {
	class LightManager
	{
	public:
		LightManager();
		~LightManager();
		void AddLight(prefab::LightBase* lig);
		void RemoveLight(prefab::LightBase* lig);
	private:
	};
}
