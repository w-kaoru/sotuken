#pragma once
#include "physics/PhysicsStaticObject.h"
class StageData;
class BackGround :public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start();
	void Update();
	void Draw();
	void Draw(int player_num);
private:
	SkinModel m_model;									//スキンモデル。
	CVector3 m_pos = CVector3::Zero();					//座標。
	CVector3 m_scale = CVector3::One();					//拡大率。
	CQuaternion m_rot = CQuaternion::Identity();		//回転。
	PhysicsStaticObject m_staticObject;                 //静的オブジェクト。
	StageData* m_stageData = nullptr;
};

