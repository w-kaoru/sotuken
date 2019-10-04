#include "stdafx.h"
#include "LightManager.h"
#include "DirectionLight.h"

namespace GameEngine {
	LightManager::LightManager()
	{
	}

	LightManager::~LightManager()
	{
	}

	void LightManager::Init()
	{
		InitDirectionLightStructuredBuffer();
		m_lightParamCB.Create(&m_lightParam, sizeof(m_lightParam));
	}

	void LightManager::AddLight(prefab::LightBase * lig)
	{
		if (m_directionLights.size() >= MAX_DIRECTION_LIGHT) {
			return;
		}
		//ライトの振り分け。
		const std::type_info& typeInfo = typeid(*lig);
		if (typeInfo == typeid(prefab::DirectionLight)) {
			//登録済みか調べる。
			auto findIt = std::find(m_directionLights.begin(), m_directionLights.end(), lig);
			if (findIt == m_directionLights.end()) {
				//新規登録。
				m_directionLights.push_back(reinterpret_cast<prefab::DirectionLight*>(lig));
			}
			else {
				//既に登録されてるよ。
				return;
			}
		}
	}

	void LightManager::RemoveLight(prefab::LightBase * lig)
	{
		const std::type_info& typeInfo = typeid(*lig);
		if (typeInfo == typeid(prefab::DirectionLight)) {
			m_directionLights.erase(
				std::remove(m_directionLights.begin(), m_directionLights.end(), lig),
				m_directionLights.end()
			);
		}
	}
	void LightManager::InitDirectionLightStructuredBuffer()
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		int stride = sizeof(SDirectionLight);

		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	//SRVとしてバインド可能。
		desc.ByteWidth = stride * MAX_DIRECTION_LIGHT;
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = stride;

		m_directionLightSB.Create(NULL, desc);
	}
	/*void LightManager::InitLightParamConstantBuffer()
	{
		//作成するバッファのサイズをsizeof演算子で求める。
		int bufferSize = sizeof(SLightParam);
		//どんなバッファを作成するのかをせてbufferDescに設定する。
		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));				//０でクリア。
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;						//バッファで想定されている、読み込みおよび書き込み方法。
		bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;	//バッファは16バイトアライメントになっている必要がある。
																	//アライメントって→バッファのサイズが16の倍数ということです。
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//バッファをどのようなパイプラインにバインドするかを指定する。
																	//定数バッファにバインドするので、D3D11_BIND_CONSTANT_BUFFERを指定する。
		bufferDesc.CPUAccessFlags = 0;								//CPU アクセスのフラグです。
																	//CPUアクセスが不要な場合は0。
		//続いて、ライト用の定数バッファを作成。		//SDirectionLightは16byteの倍数になっているので、切り上げはやらない。
		g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_lightParamCB);
	}*/
	void LightManager::Update()
	{
		//ディレクションライトのストラクチャーバッファを更新。
		int ligNo = 0;
		for (auto lig : m_directionLights) {
			m_rawDirectionLights[ligNo] = lig->GetRawData();
			ligNo++;
		}
		int numDirLig = ligNo;
		ligNo = 0;
		m_lightParam.numDirectionLight = static_cast<int>(numDirLig);
	}
	void LightManager::Render()
	{
		ID3D11DeviceContext* d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		d3dDeviceContext->VSSetConstantBuffers(1, 1, &m_lightParamCB.GetBody());
		d3dDeviceContext->PSSetConstantBuffers(1, 1, &m_lightParamCB.GetBody());
		d3dDeviceContext->VSSetShaderResources(100, 1, &m_directionLightSB.GetSRV().GetBody());
		d3dDeviceContext->PSSetShaderResources(100, 1, &m_directionLightSB.GetSRV().GetBody());
	}
}