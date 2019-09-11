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
		}
		{
			for (GameObjectList objList : m_gameObjectList) {
				for (IGameObject* obj : objList) {
					obj->PreDrawWrapper();
				}
			}
			for (GameObjectList objList : m_gameObjectList) {
				for (IGameObject* obj : objList) {
					obj->DrawWrapper();
				}
			}
			for (GameObjectList objList : m_gameObjectList) {
				for (IGameObject* obj : objList) {
					obj->PostDrawWrapper();
				}
			}
		}
		DeleteExecute();
	}

	void GameObjectManager::DeleteExecute()
	{
		int preBufferNo = m_deleteNo;
		//�o�b�t�@��؂�ւ��B
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