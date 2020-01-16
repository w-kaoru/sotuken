#pragma once
#include "RenderTarget.h"
#include "graphics/Shader.h"
#include "GaussianBlur.h"

class PostEffect;

/// <summary>
/// �u���[��
/// </summary>
class Bloom :public NonCopyable
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Bloom();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Bloom();
	void Init();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw(PostEffect& postEffect);
private:
	/// <summary>
	/// �A���t�@�u�����f�B���O�̃X�e�[�g������������B
	/// </summary>
	void InitAlphaBlendState();

	/// <summary>
	/// �V�F�[�_�[���������B
	/// </summary>
	void InitShader();
	/// <summary>
	/// �����_�����O�^�[�Q�b�g�̏������B
	/// </summary>
	void InitRenderTarget();
	/// <summary>
	/// �T���v���X�e�[�g�̏������B
	/// </summary>
	void InitSamplerState();
private:
	static const int NUM_DOWN_SAMPLE = 4;				//�_�E���T���v�����O�̉񐔁B
	ID3D11SamplerState* m_samplerState = nullptr;		//�T���v���X�e�[�g�B
	ID3D11BlendState* m_disableBlendState = nullptr;	//�A���t�@�u�����f�B���O�𖳌��ɂ���u�����f�B���O�X�e�[�g�B
	ID3D11BlendState* m_finalBlendState = nullptr;		//�ŏI�����p�̃u�����f�B���O�X�e�[�g�B
	RenderTarget m_luminanceRT;			//�P�x�𒊏o���郌���_�����O�^�[�Q�b�g
	RenderTarget m_blurCombineRT;		//�u���[�̉摜���������郌���_�����O�^�[�Q�b�g�B
	Shader m_vs;						//�������Ȃ����_�V�F�[�_�[�B
	Shader m_psLuminance;				//�P�x���o�p�̃s�N�Z���V�F�[�_�[�B
	Shader m_psCombine;					//�ڂ����摜�����p�̃s�N�Z���V�F�[�_�[�B
	Shader m_psFinal;					//�ŏI�����p�̃s�N�Z���V�F�[�_�[�B
	GaussianBlur m_gausianBlur[NUM_DOWN_SAMPLE];	//�P�x���ڂ������߂̃K�E�V�A���u���[�B
													//1/2��1/4��1/8��1/16�̉𑜓x�܂Ń_�E���T���v�����O����Ă����܂��B
};

