#pragma once
class Timer
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Timer();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Timer();
	/// <summary>
	/// �^�C�}�[�̃X�^�[�g
	/// �i������Ă񂾏u�Ԃ���v���j
	/// </summary>
	void TimerStart();
	/// <summary>
	/// �^�C�}�[�����X�^�[�g���܂��B
	/// �i�������Ԃ�ێ������܂܂�����x�X�^�[�g���܂��j
	/// </summary>
	void TimerRestart();
	/// <summary>
	/// �X�g�b�v�֐�
	/// �i�X�g�b�v�E�H�b�`�̃��b�v�̂悤�Ȋ֐��j
	/// ���Ԃ���肽���Ƃ��ɕK���Ă�ł��������I�I
	/// </summary>
	void TimerStop();
	/// <summary>
	/// ���b�v�X�^�[�g����̕b��Ԃ�
	/// </summary>
	/// <returns>
	/// �o�ߕb�ifloat�j
	/// </returns>
	const float GetSeconds()
	{
		return (float)m_elapsed;
	}
	/// <summary>
	/// ���b�v�X�^�[�g����̕��i���ԁj��Ԃ�
	/// </summary>
	/// <returns>
	/// �o�߁@���i���ԁj�ifloat�j
	/// </returns>
	int GetMinute()
	{
		return (int)m_elapsed / 60;
	}
	/// <summary>
	/// �X�^�[�g����̕b��Ԃ�
	/// �i���b�v�֌W�Ȃ��̂��ׂĂ̍��v�j
	/// </summary>
	/// <returns>
	/// ���v�o�ߕb�ifloat�j
	/// </returns>
	float GetAllSeconds()
	{
		return (float)m_Allelapsed;
	}
	void SetAllelapsed(double i)
	{
		m_Allelapsed = i;
	}
	/// <summary>	
	/// �X�^�[�g����̕���Ԃ�
	/// �i���b�v�֌W�Ȃ��̂��ׂĂ̍��v�j
	/// </summary>
	/// <returns>
	/// ���v�o�߁@���i���ԁj(float)
	/// </returns>
	int GetAllMinute()
	{
		return (int)m_Allelapsed / 60.0f;
	}
private:
	LONGLONG m_start = 0;				//�X�^�[�g�������̕b��
	LONGLONG m_stop = 0;				//�X�g�b�v�������̕b��
	LONGLONG m_fleam = 0;				//�X�g�b�v�������̃t���[����
	double m_elapsed = 0;				//�o�ߎ���(�P�ʁF�b)
	double m_Allelapsed = 0.0;			//���ׂĂ̌o�ߎ���(�P�ʁF�b)

};