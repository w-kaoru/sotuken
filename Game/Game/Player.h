#pragma once
#include "character/CharacterController.h"
#include "character/CharacterControllerToBox.h"
class BulletManeger;
class TankData;
class Game;
class GameCamera;
class Player:public IGameObject
{
public:
	Player();
	~Player();
	bool Start() override;
	void OnDestroy()override;
	void FireBullets(float speed);
	void Move();						//�ړ�����
	void Turn();						//��]�����B�@
	void HpGage();
	void Aiming();
	void BulletSprite();
	void Update()override;
	//��Q�[�����̕`��B
	void Draw()override;
	void PostDraw()override;
	//�Q�[�����̕����`��B
	void Draw(int player_num)override;
	void PostDraw(int player_num)override;
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
	//�v���C���[�̎��S�t���O���擾(true�Ŏ��S)
	bool GetPlayerDeth()
	{
		return playerdeth;
	}
	/*float GetCameraSpeed()
	{
		return m_cameraTurnSpeed;
	}*/
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
	GameCamera* m_gamecamera = nullptr;
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
	CharacterControllerToBox m_charaCon;				//�L�����N�^�[�R���g���[���[��ǉ��B
	float m_playerHP = 100.0f;                          //�v���C���[��HP�B
	Sprite m_playerhp;                                  //�v���C���[��HP��\������X�v���C�g�B
	bool playerdeth = false;                            //�v���C���[�̎��S�t���O(true�Ŏ��S)�B
	int m_timier = 0;
	CQuaternion m_rotation = CQuaternion::Identity();
	//float m_cameraTurnSpeed = 0.02f;
	TankData* m_tankData = nullptr;
	Sprite m_aiming;
	Sprite m_bulletsprite;
	CVector3 m_aimingpos = CVector3::Zero();
	CVector3 m_gunpos = CVector3::Zero();
	bool moveflag = false;
	int m_number = 0;                                   //�v���C���[�̃i���o�[�i���Ԗڂ̃v���C���[���H�j
	CVector3 m_aimingSpriteScale = CVector3::One();
};

