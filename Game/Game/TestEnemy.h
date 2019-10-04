#pragma once
#include "character/CharacterController.h"
class BulletManeger;
class TestEnemy :public IGameObject
{
public:
	TestEnemy();
	~TestEnemy();
	bool Start() override;
	void FireBullets(float speed);
	void Move();										//移動処理。
	void Turn();										//回転処理。　
	void Update();
	void Draw();
private:

	SkinModel m_model;									//スキンモデル。
	CVector3 m_forward = CVector3::Zero();
	CVector3 m_pos = CVector3::Zero();
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CQuaternion m_rot = CQuaternion::Identity();		//回転。
	CVector3 m_scale = CVector3::One();					//スケール。
	BulletManeger* m_bulletmaneger = nullptr;
	float m_deltatime = 1.0f / 30.0f;                   //1フレームの経過時間
	CharacterController m_charaCon;						//キャラクターコントローラーを追加。

};

