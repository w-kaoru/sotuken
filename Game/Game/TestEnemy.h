#pragma once
#include "character/CharacterController.h"
#include "character/CharacterControllerToBox.h"
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
	void HPGage();
	void Update();
	void Draw();
	void PostDraw();
	CVector3 GetPosition()
	{
		return m_pos;
	}
	bool GetDeth()
	{
		return enemydeth;
	}
private:

	float StX;											//スティックのXだぜ。
	float StY;											//スティックのYだぜ。
	CVector3 m_forward = CVector3::Zero();
	CVector3 m_right = CVector3::Zero();
	SkinModel m_model;									//スキンモデル。
	CVector3 m_pos = CVector3::Zero();
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CQuaternion m_rot = CQuaternion::Identity();		//回転。
	CVector3 m_scale = CVector3::One();					//スケール。
	BulletManeger* m_bulletmaneger = nullptr;
	float m_deltatime = 1.0f / 30.0f;                   //1フレームの経過時間
	CharacterControllerToBox m_charaCon;				//キャラクターコントローラーを追加。
	int m_timier = 0;
	Sprite m_enemyhp;
	CVector3 m_Sprite_Front = CVector3::AxisZ()*-1;	    //テクスチャの前方向
	CQuaternion m_Sprite_angle = CQuaternion::Identity();	//テクスチャの回転角度
	float HP = 100.0f;
	bool enemydeth = false;
};

