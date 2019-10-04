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
		//���C�g�̐U�蕪���B
		const std::type_info& typeInfo = typeid(*lig);
		if (typeInfo == typeid(prefab::DirectionLight)) {
			//�o�^�ς݂����ׂ�B
			auto findIt = std::find(m_directionLights.begin(), m_directionLights.end(), lig);
			if (findIt == m_directionLights.end()) {
				//�V�K�o�^�B
				m_directionLights.push_back(reinterpret_cast<prefab::DirectionLight*>(lig));
			}
			else {
				//���ɓo�^����Ă��B
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

		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	//SRV�Ƃ��ăo�C���h�\�B
		desc.ByteWidth = stride * MAX_DIRECTION_LIGHT;
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = stride;

		m_directionLightSB.Create(NULL, desc);
	}
	/*void LightManager::InitLightParamConstantBuffer()
	{
		//�쐬����o�b�t�@�̃T�C�Y��sizeof���Z�q�ŋ��߂�B
		int bufferSize = sizeof(SLightParam);
		//�ǂ�ȃo�b�t�@���쐬����̂�������bufferDesc�ɐݒ肷��B
		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));				//�O�ŃN���A�B
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;						//�o�b�t�@�őz�肳��Ă���A�ǂݍ��݂���я������ݕ��@�B
		bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;	//�o�b�t�@��16�o�C�g�A���C�����g�ɂȂ��Ă���K�v������B
																	//�A���C�����g���ā��o�b�t�@�̃T�C�Y��16�̔{���Ƃ������Ƃł��B
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//�o�b�t�@���ǂ̂悤�ȃp�C�v���C���Ƀo�C���h���邩���w�肷��B
																	//�萔�o�b�t�@�Ƀo�C���h����̂ŁAD3D11_BIND_CONSTANT_BUFFER���w�肷��B
		bufferDesc.CPUAccessFlags = 0;								//CPU �A�N�Z�X�̃t���O�ł��B
																	//CPU�A�N�Z�X���s�v�ȏꍇ��0�B
		//�����āA���C�g�p�̒萔�o�b�t�@���쐬�B		//SDirectionLight��16byte�̔{���ɂȂ��Ă���̂ŁA�؂�グ�͂��Ȃ��B
		g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_lightParamCB);
	}*/
	void LightManager::Update()
	{
		//�f�B���N�V�������C�g�̃X�g���N�`���[�o�b�t�@���X�V�B
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