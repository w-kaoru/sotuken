#pragma once
namespace GameEngine {
	typedef unsigned char	GameObjectPrio;
	class IGameObject:public NonCopyable
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
		*@brief	�������B
		*/
		virtual bool Start() { return true; }
		/*!
		*@brief	�X�V�B
		*/
		virtual void Update() {};
		/*!
		*@brief	�`��B
		*/
		virtual void Draw() {};
		/*!
		*@brief	�����B
		*/
		virtual void OnDestroy() {};

		/*!
		*@brief	Draw�֐������s�����O�ɌĂ΂��`�揈���B
		*/
		virtual void PreDraw() {};

		/*!
		*@brief	Draw�֐������s���ꂽ��ŌĂ΂��`�揈���B
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
					//���������������B
					m_isStart = true;
				}
			}
		}
		void OnDestroyWrapper()
		{
			OnDestroy();

		}
		/*!
		*@brief	���S�t���O�𗧂Ă�B
		*@details
		* ���̊֐��̓G���W���̊O����͎��s���Ȃ��ł��������B
		*/
		void SetDeadMark()
		{
			m_isDead = true;
		}
		/*!
		*@brief	���s�D��x���擾�B
		*/
		GameObjectPrio GetPriority() const
		{
			return m_priority;
		}
		friend class GameObjectManager;
	protected:
		GameObjectPrio m_priority;			//!<���s�D��x
		bool m_isStart;						//!<Start�̊J�n�t���O�B
		bool m_isDead;						//!<���S�t���O�B
		unsigned int m_nameKey = 0;			//!<���O�L�[�B
	};
};