#pragma once
#include "BulletController.h"
class TestEnemy;
class Bullet:public IGameObject
{
public:
	Bullet();
	~Bullet();
	bool Start();
	void Init(int k);
	void Update();
	void Draw();
	void BulletMove();
	/// <summary>
	/// 弾のポジションを設定
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 弾の速度を設定
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
	int GetTime()
	{
		return m_bulletDeleteTime;
	}
	const BulletController &GetBulletController()
	{
		return m_bulletCon;
	}
private:
	SkinModel m_model;
	BulletController m_bulletCon;
	bool E_HitFlag = false;
	bool P_HitFlag = false;
	int m_bulletDeleteTime = 0;
	CVector3 m_position = CVector3::Zero();		//座標
	CVector3 m_moveSpeed = CVector3::Zero();	//移動速度
};

