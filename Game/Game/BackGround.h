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
	SkinModel m_model;									//�X�L�����f���B
	CVector3 m_pos = CVector3::Zero();					//���W�B
	CVector3 m_scale = CVector3::One();					//�g�嗦�B
	CQuaternion m_rot = CQuaternion::Identity();		//��]�B
	PhysicsStaticObject m_staticObject;                 //�ÓI�I�u�W�F�N�g�B
	TankData* m_tankData = nullptr;
};

