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
		*@brief	��ʕ������̕`��B
		*@param[in]	player_num	�v���C���[�̃i���o�[�B
		*/
		virtual void Draw(int player_num) {};
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
		/*!
		*@brief	Draw�֐������s���ꂽ��ł́A��ʕ������̕`��B
		*@param[in]	player_num	�v���C���[�̃i���o�[�B
		*/
		virtual void PostDraw(int player_num) {};

		void DrawWrapper()
		{
			if (m_isStart && !m_isDead) {
				Draw();
			}
		}
		void DrawWrapper(int player_num)
		{
			if (m_isStart && !m_isDead) {
				Draw(player_num);
			}
		}
		void PostDrawWrapper()
		{
			if (m_isStart && !m_isDead) {
				PostDraw();
			}
		}
		void PostDrawWrapper(int player_num)
		{
			if (m_isStart && !m_isDead) {
				PostDraw(player_num);
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
			if (m_isStart && !m_isDead && !m_isStop) {
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
		void SetIsStop(bool stop) {
			m_isStop = stop;
		}
		friend class GameObjectManager;
	protected:
		GameObjectPrio m_priority;			//!<���s�D��x
		bool m_isStart;						//!<Start�̊J�n�t���O�B
		bool m_isDead;						//!<���S�t���O�B
		bool m_isStop = false;
		unsigned int m_nameKey = 0;			//!<���O�L�[�B
	};
};