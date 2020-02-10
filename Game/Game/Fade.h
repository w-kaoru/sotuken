#pragma once
/// <summary>
/// �t�F�C�h�N���X
/// </summary>
class Fade : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Fade();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Fade();
	bool Start();
	/// <summary>
	/// �t�F�C�h�̏�Ԃ�Enum
	/// </summary>
	enum Fade_State
	{
		fadein,
		fadeout,
		idel
	};
	/// <summary>
	/// Update�֐�
	/// ��ԕω���true
	/// </summary>
	void Update();
	/// <summary>
	/// Draw�֐�
	/// </summary>
	void Draw();
	/// <summary>
	/// �t�F�[�h�C���ɑJ��
	/// </summary>
	/// <param name="taim">
	/// �t�F�[�h�ɂ����鎞�ԁi1/taim�j
	/// </param>
	void Fadein(float taim = 30.0f)
	{
		m_faderate = 1 / taim;
		m_fadestate = fadein;
	}
	/// <summary>
	/// �t�F�[�h�A�E�g�ɑJ��
	/// </summary>
	/// <param name="taim">
	/// �t�F�[�h�ɂ����鎞�ԁi1/taim�j
	/// </param>
	void Fadeout(float taim = 30.0f)
	{
		m_faderate = 1 / taim;
		m_faderate *= -1;
		m_fadestate = fadeout;
	}
	/// <summary>
	/// �t�F�[�h����߂ăA�C�h���ɑJ��
	/// </summary>
	void Fadeidel()
	{
		m_faderate = 0.0f;
		m_fadestate = idel;
	}
	/// <summary>
	/// ���݂̏�Ԃ��擾
	/// </summary>
	/// <returns>
	/// ��Ԃ�Enum�iFaid::Fade_State�j
	/// </returns>
	const Fade_State GetState()
	{
		return m_fadestate;
	}
private:
	Sprite m_texture_fade;										//�^�C�g���̃t�F�C�h�p�̃��\�[�X
	float m_faderate = 0.0f;									//�t�F�C�h�������鎞��
	float m_toumei = 0.0f;										//�t�F�C�h�̓x����
	Fade_State m_fadestate = idel;								//���݂̏��
};
extern Fade* g_fade;