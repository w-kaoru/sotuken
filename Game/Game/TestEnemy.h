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
	void Move();										//�ړ������B
	void Turn();										//��]�����B�@
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

	float StX;											//�X�e�B�b�N��X�����B
	float StY;											//�X�e�B�b�N��Y�����B
	CVector3 m_forward = CVector3::Zero();
	CVector3 m_right = CVector3::Zero();
	SkinModel m_model;									//�X�L�����f���B
	CVector3 m_pos = CVector3::Zero();
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x�B
	CQuaternion m_rot = CQuaternion::Identity();		//��]�B
	CVector3 m_scale = CVector3::One();					//�X�P�[���B
	BulletManeger* m_bulletmaneger = nullptr;
	float m_deltatime = 1.0f / 30.0f;                   //1�t���[���̌o�ߎ���
	CharacterControllerToBox m_charaCon;				//�L�����N�^�[�R���g���[���[��ǉ��B
	int m_timier = 0;
	Sprite m_enemyhp;
	CVector3 m_Sprite_Front = CVector3::AxisZ()*-1;	    //�e�N�X�`���̑O����
	CQuaternion m_Sprite_angle = CQuaternion::Identity();	//�e�N�X�`���̉�]�p�x
	float HP = 100.0f;
	bool enemydeth = false;
};

