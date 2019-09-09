#pragma once
#include "IGameObject.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();
	//���s
	void Execute();
	void DrawExecute();
	void DeleteExecute();
	/*!
	 *@brief	�Q�[���I�u�W�F�N�g��new
	 *@details
	 * ���̊֐����g�p����new�����I�u�W�F�N�g�͕K��DeleteGameObject�����s���邱�Ƃ�delete�B
	 *@param[in]	prio	���s�D�揇�ʁB
	 *@param[in]	name	�I�u�W�F�N�g���O�B
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
	//�Q�[���I�u�W�F�N�g�̃��X�g�B 				//!<Transform�B
	typedef std::list<IGameObject*>	GameObjectList;
	std::vector<GameObjectList>	m_gameObjectList;					//!<�Q�[���I�u�W�F�N�g�̗D��x�t�����X�g�B
	std::vector<GameObjectList>	m_deleteObjectList[2];
	bool startDed = false;
	int m_deleteNo = 0;
};

