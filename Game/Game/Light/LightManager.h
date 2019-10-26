#pragma once
#include "LightBase.h"
#include "Light.h"

namespace GameEngine {
	namespace prefab {
		class DirectionLight;
		class LightBase;
	}
	class LightManager
	{
	public:
		LightManager();
		~LightManager();
		void Init();
		void AddLight(prefab::LightBase* lig);
		void RemoveLight(prefab::LightBase* lig);
		void InitDirectionLightStructuredBuffer();
		void InitDirectionLightShaderResourceView();
		void InitLightParamConstantBuffer();
		//�X�V�B
		void Update();
		//�`��V�[�P���X����Ă΂�鏈���B
		void Render();
		void SetLightParam(CVector3 eyePos,int directionLightNum)
		{
			m_lightParam.eyePos = eyePos;
			m_lightParam.numDirectionLight = directionLightNum;
		}
		void SetEyePos(CVector3 pos) 
		{
			m_lightParam.eyePos = pos;
		}
	private:
		static const int MAX_DIRECTION_LIGHT = 4;						//!<�f�B���N�V�������C�g�̍ő吔�B
		/*!
		 *@brief	GPU�Ŏg�p���郉�C�g�p�̃p�����[�^�B
		 *@details
		 * �����o�ϐ���ǉ�������A���т�ς����肵����
		 * Assets/shader/modelCB.h��lightCb���ς���K�v����B
		 */
		SLightParam							m_lightParam;
		SDirectionLight						m_rawDirectionLights[MAX_DIRECTION_LIGHT];
		std::list<prefab::DirectionLight*>	m_directionLights;		//!<���s�����̃��X�g�B
		//ConstantBuffer						m_lightParamCB;
		//StructuredBuffer					m_directionLightSB;
		ID3D11Buffer*						m_lightParamCB = nullptr;		//!<�R���X�^���g�o�b�t�@�B
		ID3D11Buffer*						m_directionLightSB = nullptr;	//!<�X�g���N�`���[�o�b�t�@�B
		ID3D11ShaderResourceView*			m_directionLightSRV = nullptr;	//!<SRV�B
	};
}
