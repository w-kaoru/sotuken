#include "stdafx.h"
#include "Sprite.h"
#include "graphics/Camera.h"

struct SVertex {
	float position[4];		//���_���W�B4�v�f�Ȃ͍̂��͋C�ɂ��Ȃ��B
	float uv[2];			//UV���W�B���ꂪ�e�N�X�`�����W
};

Sprite::Sprite()
{

}


Sprite::~Sprite()
{
	if (m_vertexBuffer != nullptr) {
		m_vertexBuffer->Release();
	}
	if (m_indexBuffer != nullptr) {
		m_indexBuffer->Release();
	}
	if (m_samplerState != nullptr) {
		m_samplerState->Release();
	}
	if (m_texture != nullptr) {
		m_texture->Release();
	}
	if (m_cb != nullptr) {
		m_cb->Release();
	}
}

void Sprite::InitVertexBuffer(float w, float h)
{
	//��Œ�`�������_���g�p���Ē��_�o�b�t�@���쐬����B
	//���_�o�b�t�@���쐬���邽�߂ɂ�D3D11_BUFFER_DESC��D3D11_SUBRESOURCE_DATA��ݒ肷��K�v������B
	float halfW = w * 0.5f;
	float halfH = h * 0.5f;
	SVertex vertex[4] = {
		//���_�P
		{
			//���W�@position[4]
			-halfW,  -halfH, 0.0f, 1.0f,
			//UV���W uv[2]
			0.0f, 1.0f
		},
		//���_�Q
		{
			//���W�@position[4]
			halfW, -halfH, 0.0f, 1.0f,
			//UV���W uv[2]
			1.0f, 1.0f
		},
		//���_�R
		{
			//���W�@position[4]
			-halfW,  halfH, 0.0f, 1.0f,
			//UV���W uv[2]
			0.0f, 0.0f
		},
		//���_�S
		{
			//���W�@position[4]
			halfW,  halfH, 0.0f, 1.0f,
			//UV���W uv[2]
			1.0f, 0.0f
		},
	};
	//��Œ�`�������_���g�p���Ē��_�o�b�t�@���쐬����B
	//���_�o�b�t�@���쐬���邽�߂ɂ�D3D11_BUFFER_DESC��D3D11_SUBRESOURCE_DATA��ݒ肷��K�v������B
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));				//�\���̂�0�ŏ���������B
	bd.Usage = D3D11_USAGE_DEFAULT;				//�o�b�t�@�[�őz�肳��Ă���ǂݍ��݂���я������݂̕��@�B
												//��肠������D3D11_USAGE_DEFAULT�ł悢�B
	bd.ByteWidth = sizeof(vertex);				//���_�o�b�t�@�̃T�C�Y�B���_�̃T�C�Y�~���_���ƂȂ�B
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//���ꂩ��쐬����o�b�t�@�����_�o�b�t�@�ł��邱�Ƃ��w�肷��B

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertex;

	//���_�o�b�t�@�̍쐬�B
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &m_vertexBuffer);
}

void Sprite::Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, CVector2 pivot)
{
	//�s�{�b�g���l���ɓ��ꂽ���s�ړ��s����쐬�B
	//�s�{�b�g�͐^�񒆂�0.0, 0.0�A���オ-1.0f, -1.0�A�E����1.0�A1.0�ɂȂ�悤�ɂ���B
	CVector2 localPivot = pivot;
	localPivot.x -= 0.5f;
	localPivot.y -= 0.5f;
	localPivot.x *= -2.0f;
	localPivot.y *= -2.0f;
	//�摜�̃n�[�t�T�C�Y�����߂�B
	CVector2 halfSize = m_size;
	halfSize.x *= 0.5f;
	halfSize.y *= 0.5f;
	CMatrix mPivotTrans;

	mPivotTrans.MakeTranslation(
		{ halfSize.x * localPivot.x, halfSize.y * localPivot.y, 0.0f }
	);
	CMatrix mTrans, mRot, mScale;
	mTrans.MakeTranslation(trans);
	mRot.MakeRotationFromQuaternion(rot);
	mScale.MakeScaling(scale);
	m_world.Mul(mPivotTrans, mScale);
	m_world.Mul(m_world, mRot);
	m_world.Mul(m_world, mTrans);
}
void Sprite::Update(const CVector3 & trans, const CMatrix & rot, const CVector3 & scale, CVector2 pivot)
{
	//�s�{�b�g���l���ɓ��ꂽ���s�ړ��s����쐬�B
	//�s�{�b�g�͐^�񒆂�0.0, 0.0�A���オ-1.0f, -1.0�A�E����1.0�A1.0�ɂȂ�悤�ɂ���B
	CVector2 localPivot = pivot;
	localPivot.x -= 0.5f;
	localPivot.y -= 0.5f;
	localPivot.x *= -2.0f;
	localPivot.y *= -2.0f;
	//�摜�̃n�[�t�T�C�Y�����߂�B
	CVector2 halfSize = m_size;
	halfSize.x *= 0.5f;
	halfSize.y *= 0.5f;
	CMatrix mPivotTrans;

	mPivotTrans.MakeTranslation(
		{ halfSize.x * localPivot.x, halfSize.y * localPivot.y, 0.0f }
	);
	CMatrix mTrans, mScale;
	mTrans.MakeTranslation(trans);
	mScale.MakeScaling(scale);
	m_world.Mul(mPivotTrans, mScale);
	m_world.Mul(m_world, rot);
	m_world.Mul(m_world, mTrans);
}
void Sprite::InitIndexBuffer()
{
	//���ꂪ�C���f�b�N�X�B���_�ԍ��B
	int index[6] = {
		0,1,2,		//�O�p�`���
		2,1,3		//�O�p�`���
	};
	//��Œ�`�����C���f�b�N�X���g�p���ăC���f�b�N�X�o�b�t�@���쐬����B
	//�C���f�b�N�X�o�b�t�@�̍쐬�����_�o�b�t�@�Ɠ��l�ɁA
	//D3D11_BUFFER_DESC��D3D11_SUBRESOURCE_DATA��ݒ肷��K�v������B
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));				//�\���̂�0�ŏ���������B
	bd.Usage = D3D11_USAGE_DEFAULT;				//�o�b�t�@�[�őz�肳��Ă���ǂݍ��݂���я������݂̕��@�B
												//��肠������D3D11_USAGE_DEFAULT�ł悢�B
	bd.ByteWidth = sizeof(index);				//�C���f�b�N�X�o�b�t�@�̃T�C�Y�B
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;		//���ꂩ��쐬����o�b�t�@���C���f�b�N�X�o�b�t�@�ł��邱�Ƃ��w�肷��B

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = index;

	//�C���f�b�N�X�o�b�t�@�̍쐬�B
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(
		&bd, &InitData, &m_indexBuffer
	);
}
void Sprite::InitConstantBuffer()
{
	D3D11_BUFFER_DESC desc;

	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = (((sizeof(ConstantBuffer) - 1) / 16) + 1) * 16;	//16�o�C�g�A���C�����g�ɐ؂肠����B
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc, NULL, &m_cb);
}
void Sprite::InitSamplerState()
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
}
void Sprite::InitCommon(float w, float h)
{
	m_size.x = w;
	m_size.y = h;
	//���_�o�b�t�@�̏������B
	InitVertexBuffer(w, h);
	//�C���f�b�N�X�o�b�t�@�̏������B
	InitIndexBuffer();
	//�T���v���X�e�[�g�̏������B
	InitSamplerState();
	//�V�F�[�_�[�̃��[�h�B
	m_vs.Load("Assets/shader/sprite.fx", "VSMain", Shader::EnType::VS);
	m_ps.Load("Assets/shader/sprite.fx", "PSMain", Shader::EnType::PS);

	//�萔�o�b�t�@���������B
	InitConstantBuffer();

}
void Sprite::Init(const wchar_t* texFilePath, float w, float h)
{
	//���ʂ̏������������ĂԁB
	InitCommon(w, h);

	//�e�N�X�`�������[�h�B
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(),	//D3D�f�o�C�X�B
		texFilePath,						//�ǂݍ��މ摜�f�[�^�̃t�@�C���p�X�B
		0,
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_SHADER_RESOURCE,
		0,
		0,
		false,
		nullptr,
		&m_texture					//�ǂݍ��񂾃e�N�X�`����
									//�A�N�Z�X���邽�߂̃C���^�[�t�F�[�X�̊i�[��B
	);
}
void Sprite::Init(ID3D11ShaderResourceView* srv, float w, float h)
{
	//���ʂ̏������������Ăяo���B
	InitCommon(w, h);
	m_texture = srv;
	if (m_texture != nullptr) {
		m_texture->AddRef();	//�Q�ƃJ�E���^�𑝂₷�B
	}
}
//Sprite::Draw�֐��̎����B
void Sprite::Draw(const CMatrix& viewMatrix, const CMatrix& projMatrix)
{
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();

	unsigned int vertexSize = sizeof(SVertex);	//���_�̃T�C�Y�B
	unsigned int offset = 0;

	//�V�F�[�_�[��ݒ�B
	d3dDeviceContext->VSSetShader(
		(ID3D11VertexShader*)m_vs.GetBody(),
		nullptr,
		0
	);
	d3dDeviceContext->PSSetShader(
		(ID3D11PixelShader*)m_ps.GetBody(),
		nullptr,
		0
	);
	//�e�N�X�`����ݒ�B
	d3dDeviceContext->PSSetShaderResources(0, 1, &m_texture);
	//�T���v���X�e�[�g��ݒ�B
	//d3dDeviceContext->PSSetSamplers(0, 1, &m_samplerState);
	//���[���h�r���[�v���W�F�N�V�����s����쐬�B
	ConstantBuffer cb;
	cb.WVP = m_world;
	cb.WVP.Mul(cb.WVP, viewMatrix);
	cb.WVP.Mul(cb.WVP, projMatrix);
	cb.color = m_color;

	d3dDeviceContext->UpdateSubresource(m_cb, 0, NULL, &cb, 0, 0);
	d3dDeviceContext->VSSetConstantBuffers(0, 1, &m_cb);
	d3dDeviceContext->PSSetConstantBuffers(0, 1, &m_cb);
	d3dDeviceContext->IASetVertexBuffers(	//���_�o�b�t�@��ݒ�B
		0,					//StartSlot�ԍ��B����0�ł����B
		1,					//�o�b�t�@�̐��B����1�ł����B
		&m_vertexBuffer,	//���_�o�b�t�@�B
		&vertexSize,		//���_�̃T�C�Y�B
		&offset				//�C�ɂ��Ȃ��Ă悢�B
	);
	d3dDeviceContext->IASetIndexBuffer(	//�C���f�b�N�X�o�b�t�@��ݒ�B
		m_indexBuffer,			//�C���f�b�N�X�o�b�t�@�B
		DXGI_FORMAT_R32_UINT,	//�C���f�b�N�X�̃t�H�[�}�b�g�B
								//�����32bit�Ȃ̂ŁADXGI_FORMAT_R32_UINT�ł����B
		0						//�I�t�Z�b�g0�ł����B
	);
	d3dDeviceContext->IASetInputLayout(m_vs.GetInputLayout());
	//�v���~�e�B�u�̃g�|���W�[��
	//�g���C�A���O���X�g���b�v��ݒ肷��B
	d3dDeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	d3dDeviceContext->DrawIndexed(	//�`�施�߁B
		6,				//�C���f�b�N�X���B
		0,				//�J�n�C���f�b�N�X�ԍ��B0�ł����B
		0				//�J�n���_�ԍ��B0�ł����B
	);
}