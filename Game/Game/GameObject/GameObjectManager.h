#pragma once
#include "IGameObject.h"
#include "util/Util.h"
#include "ViewPortSplit/ViewPortSplit.h"
namespace GameEngine {
	class GameObjectManager:public NonCopyable
	{
	public:
		GameObjectManager();
		~GameObjectManager();
		/*!
		 *@brief	�������B
		 *@param[in]	gameObjectPrioMax	�Q�[���I�u�W�F�N�g�̗D��x�̍ő�l�B(255�܂�)
		 */
		void Init(int gameObjectPrioMax);
		//���s
		void Execute();
		void DeleteExecute();
		/*!
		*@brief	�Q�[���I�u�W�F�N�g�̖��O�L�[���쐬�B
		*/
		static unsigned int MakeGameObjectNameKey(const char* objectName)
		{
			static const unsigned int defaultNameKey = Util::MakeHash("Undefined");	//���O�L�[�B
			unsigned int hash;
			if (objectName == nullptr) {
				hash = defaultNameKey;
			}
			else {
				hash = Util::MakeHash(objectName);
			}
			return hash;
		}
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
			T * newObj = new T();
			m_gameObjectList.at(prio).push_back(newObj);
			unsigned int hash = MakeGameObjectNameKey(name);
			newObj->m_priority = prio;
			newObj->m_nameKey = hash;
			return newObj;
		}
		template<class T>
		T * FindGameObject(const char* name) {
			unsigned int nameKey = Util::MakeHash(name);
			for (auto& list : m_gameObjectList) {
				for (auto& obj : list) {
					if (nameKey == obj->m_nameKey) {
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
				gameObject->OnDestroyWrapper();
				m_deleteObjectList[m_deleteNo].at(gameObject->GetPriority()).push_back(gameObject);
				gameObject = nullptr;
			}
		}
		/*!
		 *@brief	�C���X�^���X�̎擾�B
		 */
		static GameObjectManager& Instance()
		{
			static GameObjectManager instance;
			return instance;
		}
		void SetIsAllStop(bool stop) 
		{
			m_isAllStop = stop;
		}
	private:
		//�Q�[���I�u�W�F�N�g�̃��X�g�B 				//!<Transform�B
		typedef std::list<IGameObject*>	GameObjectList;
		std::vector<GameObjectList>	m_gameObjectList;					//!<�Q�[���I�u�W�F�N�g�̗D��x�t�����X�g�B
		std::vector<GameObjectList>	m_deleteObjectList[2];
		bool startDed = false;
		int m_deleteNo = 0;
		bool m_isAllStop = false;
		static const unsigned char 			GAME_OBJECT_PRIO_MAX = 255;		//!<�Q�[���I�u�W�F�N�g�̗D��x�̍ő�l�B
		//ViewPortSplit				m_viewSprit;				//!<��ʕ�������C���X�^���X
	};
	static inline GameObjectManager& GOManager()
	{
		return GameObjectManager::Instance();
	}
	/*!
	 *@brief	�Q�[���I�u�W�F�N�g�����̃w���p�[�֐��B
	 *@param[in]	priority	�v���C�I���e�B�B
	 *@param[in]	objectName	�I�u�W�F�N�g���B(NULL�̎w��j
	 *@details
	 */
	template<class T>
	static inline T* NewGO(int priority, const char* objectName = "NULL")
	{
		return GOManager().NewGameObject<T>(priority, objectName);
	}
	/*!
	*@brief	�Q�[���I�u�W�F�N�g�̌����֐��B
	*@details
	* ���O�̌��������邽�ߒx���B
	*@param[in]	objectName	�Q�[���I�u�W�F�N�g�̖��O�B
	*
	*@return ���������C���X�^���X�̃A�h���X�B������Ȃ������ꍇ��nullptr��Ԃ��B
	*/
	template<class T>
	static inline T* FindGO(const char* objectName)
	{
		return GOManager().FindGameObject<T>(objectName);
	}
	/*!
	 *@brief	�Q�[���I�u�W�F�N�g�폜�̃w���p�[�֐��B
	 * NewGO���g�p���č쐬�����I�u�W�F�N�g�͕K��DeleteGO�����s����悤�ɁB
	 *@param[in]	go		�폜����Q�[���I�u�W�F�N�g�B
	 */
	static inline void DeleteGO(IGameObject* go)
	{
		GOManager().DeleteGameObject(go);
	}
	/*!
	 *@brief	�Q�[���I�u�W�F�N�g�폜�̊֐��B
	 * NewGO���g�p���č쐬�����I�u�W�F�N�g�͕K��DeleteGO�����s����悤�ɁB
	 *@details
	 * ���O�̌��������邽�ߒx���B
	 *@param[in]	objectName		�폜����Q�[���I�u�W�F�N�g�̖��O�B
	 */
	static inline void DeleteGO(const char* objectName)
	{
		IGameObject* go = FindGO<IGameObject>(objectName);
		GOManager().DeleteGameObject(go);
	}
};