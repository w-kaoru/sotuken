#pragma once
#include "physics/PhysicsStaticObject.h"
class TankData;
class BackGround :public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start();
	void Update();
	void Draw();
private:
	SkinModel m_model;									//スキンモデル。
	CVector3 m_pos = CVector3::Zero();					//座標。
	CVector3 m_scale = CVector3::One();					//拡大率。
	CQuaternion m_rot = CQuaternion::Identity();		//回転。
	PhysicsStaticObject m_staticObject;                 //静的オブジェクト。
	TankData* m_tankData = nullptr;
};

