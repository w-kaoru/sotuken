#pragma once
namespace GameEngine {
	namespace prefab {
		class LightBase : public IGameObject
		{
		public:
			bool Start() override final;
			void OnDestroy() override final;
		private:
			virtual bool StartSub() {};
			virtual void OnDestroySub() {};

		};
	}
}
