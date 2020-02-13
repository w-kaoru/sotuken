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
	CVector3 m_pos = CVector3::Zero();					//���W�B
	CVector3 m_scale = CVector3::One();					//�g�嗦�B
	CQuaternion m_rot = CQuaternion::Identity();		//��]�B
	PhysicsStaticObject m_staticObject;                 //�ÓI�I�u�W�F�N�g�B
	StageData* m_stageData = nullptr;
};

