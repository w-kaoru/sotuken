#pragma once
#include "BulletController.h"
class TestEnemy;
class Bullet:public IGameObject
{
public:
	Bullet();
	~Bullet();
	bool Start();
	void Update();
	void Draw();
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
	bool GetEHit()
	{
		return E_HitFlag;
	}
	bool GetPHit()
	{
		return P_HitFlag;
	}
	BulletController* GetBulletController()
	{
		return &m_bulletCon;
	}
private:
	SkinModel m_model;
	BulletController m_bulletCon;
	bool E_HitFlag = false;
	bool P_HitFlag = false;
	CVector3 m_position = CVector3::Zero();		//���W
	CVector3 m_moveSpeed = CVector3::Zero();	//�ړ����x
	TestEnemy* m_enemy = nullptr;
};
