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
		//��ʕ������Ă����ꍇ�J�����̐������������`�悷��
		for (ViewPortParam camera : m_viewPortParam)
		{
			//�r���[�|�[�g��ݒ�B
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
		//��ʕ������Ă��Ȃ��ꍇ���ʂɕ`�悷��
		//�r���[�|�[�g��ݒ�B
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
		//��ʕ������Ă����ꍇ�J�����̐������������`�悷��
		for (ViewPortParam camera : m_viewPortParam)
		{
			//�r���[�|�[�g��ݒ�B
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
		//��ʕ������Ă��Ȃ��ꍇ���ʂɕ`�悷��
		//�r���[�|�[�g��ݒ�B
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
		//�r���[�|�[�g�����폜�B
		m_viewPortParam.pop_back();
	}
}