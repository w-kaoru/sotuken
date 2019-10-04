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
	void Move();										//�ړ������B
	void Turn();										//��]�����B�@
	void Update();
	void Draw();
private:

	SkinModel m_model;									//�X�L�����f���B
	CVector3 m_forward = CVector3::Zero();
	CVector3 m_pos = CVector3::Zero();
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x�B
	CQuaternion m_rot = CQuaternion::Identity();		//��]�B
	CVector3 m_scale = CVector3::One();					//�X�P�[���B
	BulletManeger* m_bulletmaneger = nullptr;
	float m_deltatime = 1.0f / 30.0f;                   //1�t���[���̌o�ߎ���
	CharacterController m_charaCon;						//�L�����N�^�[�R���g���[���[��ǉ��B

};

