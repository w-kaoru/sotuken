#pragma once
#include <list>

/*
��ʕ�������N���X
*/
namespace GameEngine {
	/*
	*@param x		����̋���x���W
	*@param y		����̋���y���W
	*@param width	x����̉���
	*@param height	y����̏c��
	*/
	struct ViewPortParam
	{
		int x;
		int y;
		int width;
		int height;
	};
	class IGameObject;
	class ViewPortSplit
	{
	private:
		typedef std::list<IGameObject*> GameObjectList;
	public:
		ViewPortSplit();
		~ViewPortSplit();

		//�`��֐�
		void Render(std::vector<GameObjectList>& objectList);

		void PostRender(std::vector<GameObjectList>& objectList);

		/*
		*@brief ��ʕ�������ۂ̍���̋��̍��W�Ƃ�������̕�
		*@param x		����̋���x���W
		*@param y		����̋���y���W
		*@param width	x����̉���
		*@param height	y����̏c��
		*/

		void SetSplit(ViewPortParam param)
		{
			m_viewPortParam.push_back(param);
		}

		ViewPortParam GetSplit(int playerNum)
		{
			return m_viewPortParam[playerNum];
		}

		void SetCameraNum(int cameraNum)
		{
			m_cameraNum = cameraNum;
		}

		//��ʕ����J�n
		void Start()
		{
			m_isSplit = true;
		}

		//��ʕ����I��
		void Finish()
		{
			m_isSplit = false;
			Release();
		}
		//���݉�ʕ������Ă��邩��Ԃ��B
		//true�ŉ�ʕ���
		const bool Get_isSplit()
		{
			return m_isSplit;
		}

		//��ʕ����̏����J��
		void Release();
		//��ʕ�������C���X�^���X���擾�B
		static ViewPortSplit& Instance()
		{
			static ViewPortSplit instance;
			return instance;
		}
	private:
		int	m_cameraNum;
		bool m_isSplit;									//��ʕ������邩
		std::vector<ViewPortParam> m_viewPortParam;		//��ʕ�������ۂ̏��
	};
	/*
	*@brief ViewPortSprit�̃Q�b�^�[
	*/
	static inline ViewPortSplit& GetViewSplit()
	{
		return ViewPortSplit::Instance();
	}
}
