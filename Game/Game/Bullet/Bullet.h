#pragma once
#include "BulletController.h"
class TestEnemy;
class Bullet:public IGameObject
{
public:
	Bullet();
	~Bullet();
	bool Start();
	void Init(int collision, int number);
	void Update();
	void Draw();
	void Draw(int player_num);
	void BulletMove();
	CVector3 GetPosition()
	{
		return m_position;
	}
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
		return *m_bulletCon;
	}
	int GetNumber()
	{
		return m_number;
	}
	int GetHitNumber()
	{
		return m_hitNumber;
	}
	CVector3 GetHitPos()
	{
		return m_hitpos;
	}
private:
	SkinModel m_model;
	BulletController* m_bulletCon = nullptr;
	bool m_hitFlag = false;
	bool IsHit = false;
	int m_bulletDeleteTime = 0;
	CVector3 m_position = CVector3::Zero();		//座標
	CVector3 m_moveSpeed = CVector3::Zero();	//移動速度
	CQuaternion m_rotation = CQuaternion::Identity();
	int m_number = 0;
	int m_hitNumber = 0;
	prefab::CSoundSource*  m_explosionse;
	prefab::CSoundSource*  m_attsckse;
	CVector3 m_hitpos = CVector3::Zero();
};

