#pragma once
#include "character/CharacterController.h"
class BulletManeger;
class Player:public IGameObject
{
public:
	Player();
	~Player();
	bool Start() override;
	void FireBullets(float speed);
	void Move();						//�ړ�����
	void Turn();						//��]�����B�@
	void Update();
	void Draw();
	void PostDraw();
	CVector3 GetPosition()
	{
		return m_pos;
	}
private:
		 

	float StX;											//�X�e�B�b�N��X�����B
	float StY;											//�X�e�B�b�N��Y�����B
	SkinModel m_model;									//�X�L�����f���B
	wchar_t moji[256];
	GameFont m_font;
	float m_fontsize = 1.0f;							//�t�H���g�T�C�Y
	Sprite m_sprite;
	CVector3 m_forward = CVector3::Zero();
	CVector3 m_pos = CVector3::Zero();
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x�B
	CQuaternion m_rot = CQuaternion::Identity();		//��]�B
	CVector3 m_scale = CVector3::One();					//�X�P�[���B
	BulletManeger* m_bulletmaneger = nullptr;
	float m_deltatime = 1.0f / 30.0f;                   //1�t���[���̌o�ߎ���
	CharacterController m_charaCon;						//�L�����N�^�[�R���g���[���[��ǉ��B
};

