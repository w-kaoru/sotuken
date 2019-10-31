#pragma once
#include "RenderTarget.h"
class ShadowMap :public NoncCopyable
{
public:
	ShadowMap();
	~ShadowMap();
	//�������B
	void Init();
	void UpdateToPosition(CVector3 lightCameraPos, CVector3 lightCameraTarget);
	void UpdateToDirection(CVector3 lightCameraDir, CVector3 lightCameraTarget, float lightCameraLen = 50.0f);
	void RenderToShadowMap();
private:
	CVector3 m_lightCameraPosition = CVector3::Zero();	//���C�g�J�����̎��_�B
	CVector3 m_lightCameraTarget = CVector3::Zero();	//���C�g�J�����̒����_�B
	CMatrix m_lightViewMatrix = CMatrix::Identity();	//���C�g�r���[�s��B
	CMatrix m_lightProjMatrix = CMatrix::Identity();	//���C�g�v���W�F�N�V�����s��B
	RenderTarget m_shadowMapRT;							//�V���h�E�}�b�v��`�悷�郌���_�����O�^�[�Q�b�g�B
	std::vector<SkinModel*> m_shadowCasters;			//�V���h�E�L���X�^�[�̔z��B
};