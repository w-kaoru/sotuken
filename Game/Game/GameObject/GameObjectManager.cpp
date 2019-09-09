#include "stdafx.h"
#include "GameObjectManager.h"


GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::Execute()
{
}

void GameObjectManager::DrawExecute()
{
}

void GameObjectManager::DeleteExecute()
{
	int preBufferNo = m_deleteNo;
	//バッファを切り替え。
	m_deleteNo = 1 ^ m_deleteNo;
	for (GameObjectList& goList : m_deleteObjectList[preBufferNo]) {
		for (IGameObject* go : goList) {
			GameObjectPrio prio = go->m_priority;
			GameObjectList& goExecList = m_gameObjectList.at(prio);
			auto it = std::find(goExecList.begin(), goExecList.end(), go);
			goExecList.erase(it);
			delete (*it);
		}
		goList.clear();
	}
}
