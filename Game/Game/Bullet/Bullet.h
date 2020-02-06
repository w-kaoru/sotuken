#pragma once
#include "BulletController.h"
class TestEnemy;
class Bullet:public IGameObject
{
public:
	Bullet();
	~Bullet();
	bool Start();
	void Init(int k, int number);
	void Update();
	void Draw();
	void Draw(int player_num);
	void BulletMove();
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
	bool GetBulletHit()
	{
		return m_hitFlag;
	}
	bool GetHit()
	{
		return IsHit;
	}
	int GetTime()
	{
		return m_bulletDeleteTime;
	}
	const BulletController &GetBulletController()
	{
		return m_bulletCon;
	}
	int GetNumber()
	{
		return m_number;
	}
private:
	SkinModel m_model;
	BulletController m_bulletCon;
	bool m_hitFlag = false;
	bool IsHit = false;
	int m_bulletDeleteTime = 0;
	CVector3 m_position = CVector3::Zero();		//���W
	CVector3 m_moveSpeed = CVector3::Zero();	//�ړ����x
	int m_number = 0;
};

