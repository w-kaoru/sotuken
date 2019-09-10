#pragma once
namespace GameEngine {
	typedef unsigned char	GameObjectPrio;
	class IGameObject
	{
	public:
		virtual ~IGameObject() {};
		IGameObject() :
			m_priority(0),
			m_isStart(false),
			m_isDead(false)
		{
		}
		/*!
		*@brief	初期化。
		*/
		virtual bool Start() { return true; }
		/*!
		*@brief	更新。
		*/
		virtual void Update() {};
		/*!
		*@brief	描画。
		*/
		virtual void Draw() {};
		/*!
		*@brief	消去。
		*/
		virtual void Destroy() {};

		/*!
		*@brief	Draw関数が実行される前に呼ばれる描画処理。
		*/
		virtual void PreDraw() {};

		/*!
		*@brief	Draw関数が実行された後で呼ばれる描画処理。
		*/
		virtual void PostDraw() {};

		void DrawWrapper()
		{
			if (m_isStart && !m_isDead) {
				Draw();
			}
		}
		void PostDrawWrapper()
		{
			if (m_isStart && !m_isDead) {
				PostDraw();
			}
		}
		void PreDrawWrapper()
		{
			if (m_isStart && !m_isDead) {
				PreDraw();
			}
		}
		void UpdateWrapper()
		{
			if (m_isStart && !m_isDead) {
				Update();
			}
		}
		void StartWrapper()
		{
			if (!m_isStart && !m_isDead) {
				if (Start()) {
					//初期化処理完了。
					m_isStart = true;
				}
			}
		}
		//オブジェクトの名前のゲッター
		//const std::string& GetName()const
		//{
		//	return m_Name;
		//}
		////オブジェクトの名前のセッター
		//void SetName(const std::string& Name)
		//{
		//	m_Name = Name;
		//}
		/*!
		*@brief	死亡フラグを立てる。
		*@details
		* この関数はエンジンの外からは実行しないでください。
		*/
		void SetDeadMark()
		{
			m_isDead = true;
		}
		/*!
		*@brief	実行優先度を取得。
		*/
		GameObjectPrio GetPriority() const
		{
			return m_priority;
		}
		friend class GameObjectManager;
	protected:
		GameObjectPrio m_priority;			//!<実行優先度
		bool m_isStart;						//!<Startの開始フラグ。
		bool m_isDead;						//!<死亡フラグ。
		//std::string m_Name = "NULL";     	//!<インスタンスの名前
		unsigned int m_nameKey = 0;			//!<名前キー。
	};
};