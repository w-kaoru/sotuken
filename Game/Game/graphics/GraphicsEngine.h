#pragma once
#include "Sprite.h"
/*!
 *@brief	�O���t�B�b�N�X�G���W���B
 */
class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	/*!
	 *@brief	�������B
	 *@param[in]	hWnd		�E�B���h�E�n���h���B
	 */
	void Init(HWND hWnd);
	/*!
	 *@brief	����B
	 */
	void Release();
	/*!
	 *@brief	D3D11�f�o�C�X���擾�B
	 */
	ID3D11Device* GetD3DDevice()
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	D3D11�f�o�C�X�R���e�L�X�g���擾�B
	 */
	ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}
	/// <summary>
	/// �Q�[���Ńf�t�H���g�̃t�H���g���擾
	/// </summary>
	/// <returns>
	/// �t�H���g�f�[�^�iDirectX::SpriteFont*�j
	/// </returns>
	DirectX::SpriteFont* GetSpriteFont()
	{
		return m_SpriteFont;
	}
	/// <summary>
	/// �t�H���g�\���ɕK�v�ȃN���X���擾
	/// </summary>
	/// <returns>
	/// �t�H���g�\���ɕK�v�ȃN���X�iDirectX::SpriteBatch*�j
	/// </returns>
	DirectX::SpriteBatch* GetSpriteBatch()
	{
		return m_SpriteBatch;
	}
	/// <summary>
	/// ���X�^���C�U�X�e�[�g�̃Q�b�g
	/// </summary>
	/// <returns>
	/// ���X�^���C�U�X�e�[�g�iID3D11RasterizerState* �j
	/// </returns>
	ID3D11RasterizerState* GetRasterizerState()
	{
		return m_rasterizerState;
	}
	/*!
	 *@brief	�`��J�n�B
	 */
	void BegineRender();
	/*!
	 *@brief	�`��I���B
	 */
	void EndRender();
	/// <summary>
	/// �G�t�F�N�g�̃}�l�[�W���[�N���X�̎擾
	/// </summary>
	/// <returns>
	/// �G�t�F�N�g�̃}�l�[�W���[�N���X�iEffekseer::Manager*�j
	/// </returns>
	Effekseer::Manager* GetEffekseerManager()
	{
		return m_effekseerManager;
	}
	void EffectUpdate()
	{
		//�܂���Effeseer�̍s��^�̕ϐ��ɁA�J�����s��ƃv���W�F�N�V�����s����R�s�[�B
		Effekseer::Matrix44 efCameraMat;
		g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
		Effekseer::Matrix44 efProjMat;
		g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
		//�J�����s��ƃv���W�F�N�V�����s���ݒ�B
		m_effekseerRenderer->SetCameraMatrix(efCameraMat);
		m_effekseerRenderer->SetProjectionMatrix(efProjMat);
		//Effekseer���X�V�B
		m_effekseerManager->Update();
		EffectDraw();
	}
	void EffectDraw()
	{
		//�G�t�F�N�g�͕s�����I�u�W�F�N�g��`�悵����ŕ`�悷��B
		m_effekseerRenderer->BeginRendering();
		m_effekseerManager->Draw();
		m_effekseerRenderer->EndRendering();
	}
private:
	D3D_FEATURE_LEVEL		m_featureLevel;				//Direct3D �f�o�C�X�̃^�[�Q�b�g�ƂȂ�@�\�Z�b�g�B
	ID3D11Device*			m_pd3dDevice = NULL;		//D3D11�f�o�C�X�B
	IDXGISwapChain*			m_pSwapChain = NULL;		//�X���b�v�`�F�C���B
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;	//D3D11�f�o�C�X�R���e�L�X�g�B
	ID3D11RenderTargetView* m_backBuffer = NULL;		//�o�b�N�o�b�t�@�B
	ID3D11RasterizerState*	m_rasterizerState = NULL;	//���X�^���C�U�X�e�[�g�B
	ID3D11Texture2D*		m_depthStencil = NULL;		//�f�v�X�X�e���V���B
	ID3D11DepthStencilView* m_depthStencilView = NULL;	//�f�v�X�X�e���V���r���[�B
	DirectX::SpriteFont*    m_SpriteFont = NULL;		//�Q�[���̃f�t�H���g�̃t�H���g�f�[�^
	DirectX::SpriteBatch*   m_SpriteBatch = NULL;		//�Q�[���̃f�t�H���g�̃t�H���g�\���p�f�[�^
	Effekseer::Manager*	m_effekseerManager = nullptr;	//�G�t�F�N�g�}�l�[�W���[�N���X
	EffekseerRenderer::Renderer*	m_effekseerRenderer = nullptr;  //�G�t�F�N�g�����_���[�N���X

};

extern GraphicsEngine* g_graphicsEngine;			//�O���t�B�b�N�X�G���W��