#include "stdafx.h"
#include "GameObjectManager.h"

namespace GameEngine {
	GameObjectManager::GameObjectManager()
	{
	}
	GameObjectManager::~GameObjectManager()
	{
	}
	void GameObjectManager::Init(int gameObjectPrioMax)
	{
		if (gameObjectPrioMax > GAME_OBJECT_PRIO_MAX)
		{
			gameObjectPrioMax = GAME_OBJECT_PRIO_MAX;
		}
		m_gameObjectList.resize(gameObjectPrioMax);
		m_deleteObjectList[0].resize(gameObjectPrioMax);
		m_deleteObjectList[1].resize(gameObjectPrioMax);
	}
	void GameObjectManager::Execute()
	{
		for (GameObjectList objList : m_gameObjectList) {
			for (IGameObject* obj : objList) {
				obj->StartWrapper();
			}
		}

		for (GameObjectList objList : m_gameObjectList) {
			for (IGameObject* obj : objList) {
				obj->UpdateWrapper();
			}
		}
		g_graphicsEngine->GetLightManager()->Update();


		for (GameObjectList objList : m_gameObjectList) {
			for (IGameObject* obj : objList) {
				obj->PreDrawWrapper();
			}
		}
		g_graphicsEngine->PreRender();

		for (GameObjectList objList : m_gameObjectList) {
			for (IGameObject* obj : objList) {
				obj->DrawWrapper();
			}
		}
		g_physics.DebubDrawWorld();
		g_graphicsEngine->GetLightManager()->Render();
		for (GameObjectList objList : m_gameObjectList) {
			for (IGameObject* obj : objList) {
				obj->PostDrawWrapper();
			}
		}
		g_graphicsEngine->PostRender();
		DeleteExecute();
	}

	void GameObjectManager::DeleteExecute()
	{
		int preBufferNo = m_deleteNo;
		//バッファを切り替え。
		m_deleteNo = 1 ^ m_deleteNo;
		for (GameObjectList& goList : m_deleteObjectList[preBufferNo]) {
			for (IGameObject* go : goList) {
				GameObjectPrio prio = go->GetPriority();
				GameObjectList& goExecList = m_gameObjectList.at(prio);
				auto it = std::find(goExecList.begin(), goExecList.end(), go);
				delete (*it);
				goExecList.erase(it);
			}
			goList.clear();
		}
	}
}