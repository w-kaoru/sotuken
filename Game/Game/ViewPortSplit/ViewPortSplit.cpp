#include "stdafx.h"
#include "ViewPortSplit.h"


ViewPortSplit::ViewPortSplit()
{
	m_isSplit = false;
	m_cameraNum = 0;
}


ViewPortSplit::~ViewPortSplit()
{
}

void ViewPortSplit::Render(std::vector<GameObjectList>& objectList)
{
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	D3D11_VIEWPORT viewport;
	if (m_isSplit)
	{
		int cameraNum = 0;
		//画面分割していた場合カメラの数だけもう一回描画する
		for (ViewPortParam camera : m_viewPortParam)
		{
			//ビューポートを設定。
			viewport.Width = camera.width;
			viewport.Height = camera.height;
			viewport.TopLeftX = camera.x;
			viewport.TopLeftY = camera.y;
			viewport.MinDepth = 0.0f;
			viewport.MaxDepth = 1.0f;
			d3dDeviceContext->RSSetViewports(1, &viewport);
			for (GameObjectList objList : objectList) {
				for (IGameObject* obj : objList) {
					obj->DrawWrapper(cameraNum);
				}
			}
			cameraNum++;
		}
	}
	else
	{
		//画面分割していない場合普通に描画する
		//ビューポートを設定。
		viewport.Width = FRAME_BUFFER_W;
		viewport.Height = FRAME_BUFFER_H;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		d3dDeviceContext->RSSetViewports(1, &viewport);
		for (GameObjectList objList : objectList) {
			for (IGameObject* obj : objList) {
				obj->DrawWrapper();
			}
		}
	}
}

void ViewPortSplit::PostRender(std::vector<GameObjectList>& objectList)
{
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	D3D11_VIEWPORT viewport;
	if (m_isSplit)
	{
		int cameraNum = 0;
		//画面分割していた場合カメラの数だけもう一回描画する
		for (ViewPortParam camera : m_viewPortParam)
		{
			//ビューポートを設定。
			viewport.Width = camera.width;
			viewport.Height = camera.height;
			viewport.TopLeftX = camera.x;
			viewport.TopLeftY = camera.y;
			viewport.MinDepth = 0.0f;
			viewport.MaxDepth = 1.0f;
			d3dDeviceContext->RSSetViewports(1, &viewport);
			for (GameObjectList objList : objectList) {
				for (IGameObject* obj : objList) {
					obj->PostDrawWrapper(cameraNum);
				}
			}
			cameraNum++;
		}
	}
	else
	{
		//画面分割していない場合普通に描画する
		//ビューポートを設定。
		viewport.Width = FRAME_BUFFER_W;
		viewport.Height = FRAME_BUFFER_H;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		d3dDeviceContext->RSSetViewports(1, &viewport);
		for (GameObjectList objList : objectList) {
			for (IGameObject* obj : objList) {
				obj->PostDrawWrapper();
			}
		}
	}
}
void ViewPortSplit::Release()
{
	while (!m_viewPortParam.empty())
	{
		//ビューポート情報を削除。
		m_viewPortParam.pop_back();
	}
}