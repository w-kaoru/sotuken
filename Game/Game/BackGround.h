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
	PhysicsStaticObject m_staticObject;                 //静的オブジェクト。
	StageData* m_stageData = nullptr;
};

