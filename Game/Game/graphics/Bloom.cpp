#include "stdafx.h"
#include "Bloom.h"
#include "Game.h"
#include "PostEffect.h"

Bloom::Bloom()
{
}


Bloom::~Bloom()
{
	if (m_disableBlendState != nullptr) {
		m_disableBlendState->Release();
	}

	if (m_samplerState != nullptr) {
		m_samplerState->Release();
	}
	if (m_finalBlendState != nullptr) {
		m_finalBlendState->Release();
	}
}

void Bloom::Init()
{
	//�e�탌���_�����O�^�[�Q�b�g�̏������B
	InitRenderTarget();
	//�V�F�[�_�[���������B
	InitShader();
	//���u�����h�X�e�[�g���������B
	InitAlphaBlendState();
	//�T���v���X�e�[�g�̏������B
	InitSamplerState();

	//�P�x�e�N�X�`�����ڂ������߂̃K�E�V�A���u���[������������B
	ID3D11ShaderResourceView* srcBlurTexture = m_luminanceRT.GetRenderTargetSRV();
	for (auto& gaussianBlur : m_gausianBlur) {
		gaussianBlur.Init(srcBlurTexture, 25.0f);
		//���̃K�E�X�u���[�Ŏg�p����\�[�X�e�N�X�`����ݒ肷��B
		srcBlurTexture = gaussianBlur.GetResultTextureSRV();
	}
}

void Bloom::InitSamplerState()
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
}
void Bloom::InitShader()
{
	m_vs.Load("Assets/shader/bloom.fx", "VSMain", Shader::EnType::VS);
	m_psLuminance.Load("Assets/shader/bloom.fx", "PSSamplingLuminance", Shader::EnType::PS);
	m_psFinal.Load("Assets/shader/bloom.fx", "PSFinal", Shader::EnType::PS);
	//�{�P�摜�����p�̃s�N�Z���V�F�[�_�[�����[�h����B
	m_psCombine.Load("Assets/shader/bloom.fx", "PSCombine", Shader::EnType::PS);
}
void Bloom::InitRenderTarget()
{
	//�P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬����B
	m_luminanceRT.Create(
		(unsigned int(FRAME_BUFFER_W)),
		(unsigned int(FRAME_BUFFER_H)),
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);
	//�t���[���o�b�t�@��1/2�̉𑜓x�̃{�P�摜�����p�̃����_�����O�^�[�Q�b�g���쐬����B
	//�ڂ������摜���ŏI�������邽�߂̃����_�����O�^�[�Q�b�g���쐬����B
	m_blurCombineRT.Create(
		(unsigned int(FRAME_BUFFER_W/2)), 
		(unsigned int(FRAME_BUFFER_H/2)),
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);
}
void Bloom::InitAlphaBlendState()
{
	CD3D11_DEFAULT defaultSettings;
	////�f�t�H���g�Z�b�e�B���O�ŏ���������B
	//CD3D11_BLEND_DESC blendDesc(defaultSettings);
	//auto device = g_graphicsEngine->GetD3DDevice();

	//device->CreateBlendState(&blendDesc, &m_disableBlendState);
	//CD3D11_DEFAULT defaultSettings;
	//�G���W���ɍ��킹��������������B
	CD3D11_BLEND_DESC blendDesc(defaultSettings);
	auto device = g_graphicsEngine->GetD3DDevice();
	D3D11_BLEND_DESC BLEND_DETE;
	BLEND_DETE.AlphaToCoverageEnable = false;
	BLEND_DETE.IndependentBlendEnable = false;
	BLEND_DETE.RenderTarget[0].BlendEnable = true;
	BLEND_DETE.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BLEND_DETE.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BLEND_DETE.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BLEND_DETE.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	BLEND_DETE.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	BLEND_DETE.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BLEND_DETE.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	
	//�ŏI�����p�̃u�����h�X�e�[�g���쐬����B
	//�ŏI�����͉��Z�����B
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;/*D3D11_BLEND_ONE;*/
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;/*D3D11_BLEND_INV_SRC_ALPHA;*/
	device->CreateBlendState(&blendDesc, &m_finalBlendState);
}
void Bloom::Draw(PostEffect& postEffect)
{
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	deviceContext->PSSetSamplers(0, 1, &m_samplerState);
	//�܂��͋P�x�𒊏o����B
	{
		//���u�����h�𖳌��ɂ���B
		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		deviceContext->OMSetBlendState(m_disableBlendState, blendFactor, 0xffffffff);

		//�P�x���o�p�̃����_�����O�^�[�Q�b�g�ɕύX����B
		g_graphicsEngine->ChangeRenderTarget(&m_luminanceRT, m_luminanceRT.GetViewport());
		//�����_�����O�^�[�Q�b�g�̃N���A�B
		float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		m_luminanceRT.ClearRenderTarget(clearColor);
		
		//�V�[�����e�N�X�`���Ƃ���B
		auto mainRTTexSRV = g_graphicsEngine->GetMainRenderTarget()->GetRenderTargetSRV();
		deviceContext->PSSetShaderResources(0, 1, &mainRTTexSRV);

		//�t���X�N���[���`��B
		postEffect.DrawFullScreenQuadPrimitive(deviceContext, m_vs, m_psLuminance);
	}
	//�����āA�P�x�e�N�X�`�����K�E�V�A���u���[�łڂ����B
	{
		for (auto& gaussianBlur : m_gausianBlur) {
			gaussianBlur.Execute(postEffect);
		}
	}
	//�K�E�X�u���[�łڂ������摜��1/2�̉𑜓x�̃����_�����O�^�[�Q�b�g���g�p���āA��������B
	{
		//�����_�����O�^�[�Q�b�g���ڂ����摜�����p�̃��m�ɂ���B
		g_graphicsEngine->ChangeRenderTarget(&m_blurCombineRT, m_blurCombineRT.GetViewport());
		//�K�E�V�A���u���[���������e�N�X�`����t0�`t3���W�X�^�ɐݒ肷��B
		for (int registerNo = 0; registerNo < NUM_DOWN_SAMPLE; registerNo++) {
			auto srv = m_gausianBlur[registerNo].GetResultTextureSRV();
			deviceContext->PSSetShaderResources(registerNo, 1, &srv);
		}

		//�t���X�N���[���`��B
		postEffect.DrawFullScreenQuadPrimitive(deviceContext, m_vs, m_psCombine);
	}
	//�Ō�ɂڂ������G�����Z�����Ń��C�������_�����O�^�[�Q�b�g�ɍ������ďI���B
	{
		auto mainRT = g_graphicsEngine->GetMainRenderTarget();
		g_graphicsEngine->ChangeRenderTarget(mainRT, mainRT->GetViewport());

		//���������{�P�e�N�X�`���̃A�h���X��t0���W�X�^�ɐݒ肷��B
		auto srv = m_blurCombineRT.GetRenderTargetSRV();
		deviceContext->PSSetShaderResources(0, 1, &srv);

		//���Z�����p�̃u�����f�B���O�X�e�[�g��ݒ肷��B
		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		deviceContext->OMSetBlendState(m_finalBlendState, blendFactor, 0xffffffff);
		//�t���X�N���[���`��B
		postEffect.DrawFullScreenQuadPrimitive(deviceContext, m_vs, m_psFinal);

		//�u�����f�B���O�X�e�[�g��߂��B
		deviceContext->OMSetBlendState(m_disableBlendState, blendFactor, 0xffffffff);
	}
}