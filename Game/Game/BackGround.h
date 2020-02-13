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
	SkinModel m_model;									//�X�L�����f���B
	PhysicsStaticObject m_staticObject;                 //�ÓI�I�u�W�F�N�g�B
	StageData* m_stageData = nullptr;
};

