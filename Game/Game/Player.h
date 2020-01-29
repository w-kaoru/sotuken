#pragma once
#include "character/CharacterController.h"
#include "character/CharacterControllerToBox.h"
class BulletManeger;
class TankData;
class Game;
class Player:public IGameObject
{
public:
	Player();
	~Player();
	bool Start() override;
	void FireBullets(float speed);
	void Move();						//�ړ�����
	void Turn();						//��]�����B�@
	void HpGage();
	void Aiming();
	void BulletSprite();
	void Update();
	void Draw();
	void PostDraw();
	CVector3 GetPosition()
	{
		return m_pos;
	}
	void SetPosition(CVector3 pos)
	{
		m_pos = pos;
		m_charaCon.SetPosition(m_pos);
	}
	CVector3 GetForward()
	{
		return m_forward;
	}
	bool GetPlayerDeth()
	{
		return playerdeth;
	}
	float GetCameraSpeed()
	{
		return m_cameraTurnSpeed;
	}
	void SetNumber(int no) {
		m_number = no;
	}
	int GetNumber() {
		return m_number;
	}
	void SetMoveFlag(bool move)
	{
		moveflag = move;
	}
private:
	float StX;											//�X�e�B�b�N��X�����B
	float StY;											//�X�e�B�b�N��Y�����B
	SkinModel m_model;									//�X�L�����f���B
	SkinModel m_model2;
	Game* m_game = nullptr;
	wchar_t moji[256];
	GameFont m_font;
	float m_fontsize = 1.0f;							//�t�H���g�T�C�Y
	CVector3 m_forward = CVector3::Zero();
	CVector3 m_gunForward = CVector3::Zero();
	CVector3 m_right = CVector3::Zero();
	CVector3 m_pos = CVector3::Zero();
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x�B
	CQuaternion m_rot = CQuaternion::Identity();		//��]�B
	CVector3 m_scale = CVector3::One();					//�X�P�[���B
	BulletManeger* m_bulletmaneger = nullptr;
	float m_deltatime = 1.0f / 30.0f;                   //1�t���[���̌o�ߎ���
	CharacterControllerToBox m_charaCon;					//�L�����N�^�[�R���g���[���[��ǉ��B
	float m_playerHP = 100.0f;
	Sprite m_playerhp;
	bool playerdeth = false;
	int m_timier = 0;
	CQuaternion m_rotation = CQuaternion::Identity();
	float m_cameraTurnSpeed = 0.02f;
	TankData* m_tankData = nullptr;
	Sprite m_aimng;
	Sprite m_bulletsprite;
	CVector3 m_aimingpos = CVector3::Zero();
	CVector3 m_gunpos = CVector3::Zero();
	bool moveflag = false;
	int m_number = 0;
};

