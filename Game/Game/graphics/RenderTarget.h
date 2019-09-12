#pragma once
class RenderTarget
{
public:
	RenderTarget();
	~RenderTarget();
	// �����_�����O�^�[�Q�b�g�̉���B
	void Release();

	// �����_�����O�^�[�Q�b�g�̍쐬�B
	void Create(unsigned int w, unsigned int h, DXGI_FORMAT texFormat);

	// �����_�����O�^�[�Q�b�g�ƃf�v�X�X�e���V���̃N���A�B
	void ClearRenderTarget(float* clearColor);

	// �����_�����O�^�[�Q�b�g�r���[���擾�B
	ID3D11RenderTargetView* GetRenderTargetView()
	{
		return m_renderTargetView;
	}

	// �f�v�X�X�e���V���r���[���擾�B
	ID3D11DepthStencilView* GetDepthStensilView()
	{
		return m_depthStencilView;
	}
	// �����_�����O�^�[�Q�b�g��SRV���擾�B
	ID3D11ShaderResourceView* GetRenderTargetSRV()
	{
		return m_renderTargetSRV;
	}
	// �r���[�|�[�g�̎擾�B
	D3D11_VIEWPORT* GetViewport()
	{
		return &m_viewport;
	}
	/// <summary>
	/// �����_�����O�^�[�Q�b�g�̕����擾�B
	/// </summary>
	/// <returns></returns>
	float GetWidth() const
	{
		return m_width;
	}
	/// <summary>
	/// �����_�����O�^�[�Q�b�g�̍������擾�B
	/// </summary>
	/// <returns></returns>
	float GetHeight() const
	{
		return m_height;
	}
	/// <summary>
	/// �����_�����O�^�[�Q�b�g�ƂȂ��Ă���e�N�X�`���̃t�H�[�}�b�g���擾�B
	/// </summary>
	/// <returns></returns>
	DXGI_FORMAT GetTextureFormat() const
	{
		return m_format;
	}
private:
	float m_width = 0;												//�����_�����O�^�[�Q�b�g�̕��B
	float m_height = 0;												//�����_�����O�^�[�Q�b�g�̍����B
	DXGI_FORMAT m_format = DXGI_FORMAT_UNKNOWN;						//�����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g�B
	ID3D11Texture2D *			m_renderTargetTex = nullptr;		//�����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`���B
	ID3D11RenderTargetView*		m_renderTargetView = nullptr;		//�����_�[�^�[�Q�b�g�r���[�B
	ID3D11ShaderResourceView*	m_renderTargetSRV = nullptr;		//�����_�����O�^�[�Q�b�g��SRV
	ID3D11Texture2D*			m_depthStencilTex = nullptr;		//�f�v�X�X�e���V���ƂȂ�e�N�X�`���B
	ID3D11DepthStencilView*		m_depthStencilView = nullptr;		//�f�v�X�X�e���V���r���[�B
	D3D11_VIEWPORT				m_viewport;							//�r���[�|�[�g�B
};
