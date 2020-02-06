#pragma once
class Sky:public IGameObject
{
public:
	Sky();
	~Sky();
	bool Start();
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// �`��֐�
	/// </summary>
	void Draw();
	/// <summary>
	/// �����`��֐�
	/// </summary>
	void Draw(int player_num);
	/// <summary>
	/// �X�P�[�����Đݒ肷��֐�
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(CVector3 scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// �|�W�V�������Z�b�g����֐�
	/// </summary>
	/// <param name="pos">�|�W�V����(CVector3)</param>
	void SetPositon(CVector3& pos)
	{
		m_position = pos;
	}

private:
	SkinModel m_skymodel;
	CVector3 m_scale = CVector3::One();
	CVector3 m_position = CVector3::Zero();
	ID3D11ShaderResourceView*	m_srv = nullptr;	//SRV
	bool						m_isValid = false;	//�L�����ǂ����̃t���O
};

