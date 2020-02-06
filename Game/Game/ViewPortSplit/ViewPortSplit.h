#pragma once
#include <list>

/*
画面分割するクラス
*/
namespace GameEngine {
	/*
	*@param x		左上の隅のx座標
	*@param y		左上の隅のy座標
	*@param width	xからの横幅
	*@param height	yからの縦幅
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

		//描画関数
		void Render(std::vector<GameObjectList>& objectList);

		void PostRender(std::vector<GameObjectList>& objectList);

		/*
		*@brief 画面分割する際の左上の隅の座標とそこからの幅
		*@param x		左上の隅のx座標
		*@param y		左上の隅のy座標
		*@param width	xからの横幅
		*@param height	yからの縦幅
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

		//画面分割開始
		void Start()
		{
			m_isSplit = true;
		}

		//画面分割終了
		void Finish()
		{
			m_isSplit = false;
			Release();
		}
		//現在画面分割しているかを返す。
		//trueで画面分割
		const bool Get_isSplit()
		{
			return m_isSplit;
		}

		//画面分割の情報を開放
		void Release();
		//画面分割するインスタンスを取得。
		static ViewPortSplit& Instance()
		{
			static ViewPortSplit instance;
			return instance;
		}
	private:
		int	m_cameraNum;
		bool m_isSplit;									//画面分割するか
		std::vector<ViewPortParam> m_viewPortParam;		//画面分割する際の情報
	};
	/*
	*@brief ViewPortSpritのゲッター
	*/
	static inline ViewPortSplit& GetViewSplit()
	{
		return ViewPortSplit::Instance();
	}
}
