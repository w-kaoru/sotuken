#pragma once
#include "RenderTarget.h"
#include "SkinModel.h"
class ShadowMap :public NonCopyable
{
public:
	ShadowMap();
	~ShadowMap();

	// ���C�g�r���[�s����擾�B
	CMatrix GetLighViewMatrix() const
	{
		return m_lightViewMatrix;
	}

	// ���C�g�v���W�F�N�V�����s����擾�B
	CMatrix GetLightProjMatrix() const
	{
		return m_lightProjMatrix;
	}
	//�������B
	void Init();
	void UpdateFromLightTarget(CVector3 lightCameraPos, CVector3 lightCameraTarget);
	void UpdateFromLightDirection(CVector3 lightCameraPos, CVector3 lightDir);
	void RenderToShadowMap();
	void InitConstantBuffer();
	// �V���h�E�L���X�^�[��o�^�B
	// ���̊֐����g���āA�o�^���ꂽ�L���X�^�[��
	// �V���h�E�}�b�v�ɕ`�悳��܂��B
	// �o�^���ꂽ�L���X�^�[�̃��X�g��RenderToShadowMap���Ăяo������
	// �N���A����邽�߁A��ɉe�𐶐��������ꍇ�́A
	// ���t���[�����̊֐����Ăяo���K�v������܂��B
	void RegistShadowCaster(SkinModel* shadowCaster)
	{
		m_shadowCasters.push_back(shadowCaster);
	}
	// �V���h�E�L���X�^�[�����X�g���珜�O����B
	void UnregistShadowCaster(SkinModel* shadowCaster)
	{
		//shadowCaster�̃C���X�^���X�����X�g���猟������B
		auto it = std::find(
			m_shadowCasters.begin(),
			m_shadowCasters.end(),
			shadowCaster
		);
		if (it != m_shadowCasters.end()) {
			//���������̂ŃR���e�i���珜�O����B
			m_shadowCasters.erase(it);
		}
	}
	// �V���h�E�}�b�v��SRV���擾�B
	// <returns>�V���h�E�}�b�v��SRV</returns>
	ID3D11ShaderResourceView* GetShadowMapSRV()
	{
		return m_shadowMapRT.GetRenderTargetSRV();
	}
	struct SLightCameraParam
	{
		CMatrix mLightView;		//todo ���C�g�r���[�s��B
		CMatrix mLightProj;		//todo ���C�g�v���W�F�N�V�����s��B
	};
	void SetWidthHeight(float w,float h) {
		m_width = w;
		m_height = h;
	}
private:
	CVector3 m_lightCameraPosition = CVector3::Zero();	//���C�g�J�����̎��_�B
	CVector3 m_lightCameraTarget = CVector3::Zero();	//���C�g�J�����̒����_�B
	CMatrix m_lightViewMatrix = CMatrix::Identity();	//���C�g�r���[�s��B
	CMatrix m_lightProjMatrix = CMatrix::Identity();	//���C�g�v���W�F�N�V�����s��B
	RenderTarget m_shadowMapRT;							//�V���h�E�}�b�v��`�悷�郌���_�����O�^�[�Q�b�g�B
	std::vector<SkinModel*> m_shadowCasters;			//�V���h�E�L���X�^�[�̔z��B
	ID3D11Buffer* m_shadowMapCB = nullptr;
	SLightCameraParam m_ligCamParam;
	float m_width = 1500.0f;
	float m_height = 1500.0f;
};