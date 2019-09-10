#include "stdafx.h"
#include "GameObjectManager.h"

namespace GameEngine {
	void GameObjectManager::Execute()
	{
		{
			for (auto& objList : m_gameObjectList) {
				for (auto& obj : objList) {
					obj->StartWrapper();
				}
			}

			for (auto& objList : m_gameObjectList) {
				for (auto& obj : objList) {
					obj->UpdateWrapper();
				}
			}
		}
		{
			for (auto& objList : m_gameObjectList) {
				for (auto& obj : objList) {
					obj->PreDrawWrapper();
				}
			}
			for (auto& objList : m_gameObjectList) {
				for (auto& obj : objList) {
					obj->DrawWrapper();
				}
			}
			for (auto& objList : m_gameObjectList) {
				for (auto& obj : objList) {
					obj->PostDrawWrapper();
				}
			}
		}
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
				goExecList.erase(it);
				delete (*it);
			}
			goList.clear();
		}
	}
}