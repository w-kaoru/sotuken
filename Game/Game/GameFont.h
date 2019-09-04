#pragma once
class GameFont
{
public:
	GameFont();
	~GameFont();
	/// <summary>
	/// �t�H���g��ݒ�B
	/// </summary>
	/// <param name="font">
	/// DirectX::SpriteFont���g�p���ĕύX�B�iDirectX::SpriteFont*�j
	/// </param>
	void SetFont(DirectX::SpriteFont* font)
	{
		delete m_spriteFont;
		m_spriteFont = font;
	}
	/// <summary>
	/// �`��J�n�B
	/// </summary>
	void BeginDraw();
	/// <summary>
	/// �`��I��
	/// </summary>
	/// <remarks>
	/// ���̂܂܂��Ɠ��߂Ȃǂ̐ݒ肪�ύX����Ă܂܂Ȃ̂ŖY�ꂸ�ɌĂяo���Ă��������B
	/// </remarks>
	void EndDraw();
	/// <summary>
	/// �t�H���g�̕`��B
	/// </summary>
	/// <param name="text">
	/// �\���������e�L�X�g�B
	/// </param>
	/// <param name="position">
	/// �t�H���g��\��������W�B
	/// ���W�n�́A��ʂ̍��オ(-FRAME_BUFFER_W/2�AFRAME_BUFFER_H/2)
	/// ��ʂ̉E����(FRAME_BUFFER_W/2�A-FRAME_BUFFER_H/2)�ƂȂ��Ă���B
	/// </param>
	/// <param name="color">
	/// �����̐F
	/// </param>
	/// <param name="rotation">
	/// �����̉�]
	/// </param>
	/// <param name="scale">
	/// �傫��
	/// </param>
	/// <param name="pivot">
	/// 2D��łǂ����N�_�ɂ��邩
	///	0.5, 0.5�ŉ摜�̒��S����_�B
	///	0.0, 0.0�ŉ摜�̍����B
	///	1.0, 1.0�ŉ摜�̉E��B
	/// Unity��uGUI�ɏ����B
	/// </param>
	void Draw(
		wchar_t const* text,
		const CVector2& position,
		const CVector4& color = CVector4::White(),
		float rotation = 0.0f,
		float scale = 1.0f,
		CVector2 pivot = { 0.5f, 0.5f }
	);
private:
	DirectX::SpriteBatch*	m_spriteBatch = nullptr;	//�X�v���C�g�o�b�`�B
	DirectX::SpriteFont*	m_spriteFont = nullptr;		//�X�v���C�g�t�H���g�B
	CMatrix m_scaleMat = CMatrix::Identity();			//�g��s��
};

