#pragma once
#include "graphics/Shader.h"
#include <algorithm>

class Sprite
{
public:
	Sprite();
	~Sprite();
	/// <summary>
	/// �������B
	/// </summary>
	/// <param name="texFilePath">�e�N�X�`���̃t�@�C���p�X</param>
	/// <param name="w">�摜�̕�</param>
	/// <param name="h">�摜�̍���</param>
	void Init(const wchar_t* texFilePath, float w, float h);
	/// <summary>
	/// �e�N�X�`����SRV���w�肵�ď������B
	/// </summary>
	/// <param name="srv"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	void Init(ID3D11ShaderResourceView* srv, float w, float h);
	/// <summary>
	/// �X�V�B
	/// </summary>
	/// <param name="trans">���s�ړ���</param>
	/// <param name="rot">��]</param>
	/// <param name="scale">�g�嗦</param>
	/// <param name="pivot">
	/// �s�{�b�g
	/// 0.5, 0.5�ŉ摜�̒��S����_�B
	///	0.0, 0.0�ŉ摜�̍����B
	///	1.0, 1.0�ŉ摜�̉E��B
	///	Unity��uGUI�ɏ����B
	/// </param>
	void Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, CVector2 pivot = { 0.5f, 0.5f });
	void Update(const CVector3& trans, const CMatrix& rot, const CVector3& scale, CVector2 pivot = { 0.5f, 0.5f });
	/// <summary>
	/// �`��
	/// </summary>
	void Draw(const CMatrix& viewMatrix, const CMatrix& projMatrix);
	/// <summary>
	/// ����ψʂ�����
	/// </summary>
	/// <param name="delta">��Z����ψʂ������</param>
	void DeltaAlpha(float delta)
	{
		m_alpha += delta;
		//���l�̋��E�`�F�b�N�B
		if (m_alpha > 1.0f) {
			m_alpha = 1.0f;
		}
		else if (m_alpha < 0.0f) {
			m_alpha = 0.0f;
		}
	}
	void SetAlpha(float alpha)
	{
		m_alpha = alpha;
	}
	float GetAlpha()
	{
		return m_alpha;
	}
private:
	/// <summary>
	/// �������̋��ʏ����B
	/// </summary>
	void InitCommon(float w, float h);
	/// <summary>
	/// �萔�o�b�t�@�̏������B
	/// </summary>
	void InitConstantBuffer();

	/// <summary>
	/// ���_�o�b�t�@�̏������B
	/// </summary>
	/// <param name="w">�摜�̕�</param>
	/// <param name="h">�摜�̍���</param>
	void InitVertexBuffer(float w, float h);

	/// <summary>
	/// �C���f�b�N�X�o�b�t�@�̏������B
	/// </summary>
	void InitIndexBuffer();

	/// <summary>
	/// �T���v���X�e�[�g�̏������B
	/// </summary>
	void InitSamplerState();
private:
	struct ConstantBuffer {
		CMatrix WVP;		//���[���h�r���[�v���W�F�N�V�����s��B
		float alpha;		//���l�B
	};
	ID3D11Buffer*				m_vertexBuffer = NULL;					//���_�o�b�t�@�B
	ID3D11Buffer*				m_indexBuffer = NULL;					//�C���f�b�N�X�o�b�t�@�B
	Shader						m_vs;									//���_�V�F�[�_�[�B
	Shader						m_ps;									//�s�N�Z���V�F�[�_�[�B
	ID3D11ShaderResourceView*	m_texture = NULL;						//�e�N�X�`���B
	ID3D11SamplerState*			m_samplerState = NULL;					//�T���v���X�e�[�g�B
	CVector3					m_position = CVector3::Zero();			//���W�B
	CQuaternion					m_rotation = CQuaternion::Identity();	//��]
	CVector3					m_scale = CVector3::One();
	CMatrix						m_world = CMatrix::Identity();			//���[���h�s��B
	CVector2					m_size = CVector2::Zero();				//�摜�̃T�C�Y�B
	ID3D11Buffer*				m_cb = nullptr;							//�萔�o�b�t�@�B
	float						m_alpha = 1.0f;							//�X�v���C�g�̃��l�B

};

