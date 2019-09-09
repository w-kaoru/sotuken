#pragma once
#include "IGameObject.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();
	//実行
	void Execute();
	void DrawExecute();
	void DeleteExecute();
	/*!
	 *@brief	ゲームオブジェクトのnew
	 *@details
	 * この関数を使用してnewしたオブジェクトは必ずDeleteGameObjectを実行することでdelete。
	 *@param[in]	prio	実行優先順位。
	 *@param[in]	name	オブジェクト名前。
	 */
	template<class T>
	T * NewGameObject(int prio = 0, const char* name = "NULL")
	{
		T * newObj = new T;
		newObj->SetName(name);
		m_gameObjectList.at(prio).push_back(newObj);
		return newObj;
	}
	template<class T>
	T * FindGameObject(char name) {
		for (auto& list : m_gameObjectList) {
			for (auto& obj : list) {
				if (Name == obj->GetName()) {
					return (T*)obj;
				}
			}
		}
		return nullptr;
	}
	void DeleteGameObject(IGameObject * gameObject)
	{
		if (gameObject != nullptr)
		{
			gameObject->SetDeadMark();
			m_deleteObjectList[m_deleteNo].at(gameObject->m_priority).push_back(gameObject);
			gameObject = nullptr;
		}
	}
private:
	//ゲームオブジェクトのリスト。 				//!<Transform。
	typedef std::list<IGameObject*>	GameObjectList;
	std::vector<GameObjectList>	m_gameObjectList;					//!<ゲームオブジェクトの優先度付きリスト。
	std::vector<GameObjectList>	m_deleteObjectList[2];
	bool startDed = false;
	int m_deleteNo = 0;
};

