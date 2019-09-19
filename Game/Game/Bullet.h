#pragma once
class Bullet:public IGameObject
{
public:
	Bullet();
	~Bullet();
	bool Start();
	void Update();
	void Draw();
	/// <summary>
	/// �e�̃|�W�V������ݒ�
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// �e�̑��x��ݒ�
	/// </summary>
	/// <param name="speed"></param>
	void SetMoveSpeed(CVector3 speed)
	{
		m_moveSpeed += speed;
	}
private:
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();		//���W
	CVector3 m_moveSpeed = CVector3::Zero();	//�ړ����x
};

