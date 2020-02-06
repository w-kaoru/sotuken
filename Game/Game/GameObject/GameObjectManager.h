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
		 *@brief	初期化。
		 *@param[in]	gameObjectPrioMax	ゲームオブジェクトの優先度の最大値。(255まで)
		 */
		void Init(int gameObjectPrioMax);
		//実行
		void Execute();
		void DeleteExecute();
		/*!
		*@brief	ゲームオブジェクトの名前キーを作成。
		*/
		static unsigned int MakeGameObjectNameKey(const char* objectName)
		{
			static const unsigned int defaultNameKey = Util::MakeHash("Undefined");	//名前キー。
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
		 *@brief	ゲームオブジェクトのnew
		 *@details
		 * この関数を使用してnewしたオブジェクトは必ずDeleteGameObjectを実行することでdelete。
		 *@param[in]	prio	実行優先順位。
		 *@param[in]	name	オブジェクト名前。
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
		 *@brief	インスタンスの取得。
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
		//ゲームオブジェクトのリスト。 				//!<Transform。
		typedef std::list<IGameObject*>	GameObjectList;
		std::vector<GameObjectList>	m_gameObjectList;					//!<ゲームオブジェクトの優先度付きリスト。
		std::vector<GameObjectList>	m_deleteObjectList[2];
		bool startDed = false;
		int m_deleteNo = 0;
		bool m_isAllStop = false;
		static const unsigned char 			GAME_OBJECT_PRIO_MAX = 255;		//!<ゲームオブジェクトの優先度の最大値。
		//ViewPortSplit				m_viewSprit;				//!<画面分割するインスタンス
	};
	static inline GameObjectManager& GOManager()
	{
		return GameObjectManager::Instance();
	}
	/*!
	 *@brief	ゲームオブジェクト生成のヘルパー関数。
	 *@param[in]	priority	プライオリティ。
	 *@param[in]	objectName	オブジェクト名。(NULLの指定可）
	 *@details
	 */
	template<class T>
	static inline T* NewGO(int priority, const char* objectName = "NULL")
	{
		return GOManager().NewGameObject<T>(priority, objectName);
	}
	/*!
	*@brief	ゲームオブジェクトの検索関数。
	*@details
	* 名前の検索が入るため遅い。
	*@param[in]	objectName	ゲームオブジェクトの名前。
	*
	*@return 見つかったインスタンスのアドレス。見つからなかった場合はnullptrを返す。
	*/
	template<class T>
	static inline T* FindGO(const char* objectName)
	{
		return GOManager().FindGameObject<T>(objectName);
	}
	/*!
	 *@brief	ゲームオブジェクト削除のヘルパー関数。
	 * NewGOを使用して作成したオブジェクトは必ずDeleteGOを実行するように。
	 *@param[in]	go		削除するゲームオブジェクト。
	 */
	static inline void DeleteGO(IGameObject* go)
	{
		GOManager().DeleteGameObject(go);
	}
	/*!
	 *@brief	ゲームオブジェクト削除の関数。
	 * NewGOを使用して作成したオブジェクトは必ずDeleteGOを実行するように。
	 *@details
	 * 名前の検索が入るため遅い。
	 *@param[in]	objectName		削除するゲームオブジェクトの名前。
	 */
	static inline void DeleteGO(const char* objectName)
	{
		IGameObject* go = FindGO<IGameObject>(objectName);
		GOManager().DeleteGameObject(go);
	}
};