#pragma once
#include "character/CharacterController.h"
#include "character/CharacterControllerToBox.h"
class BulletManeger;
class TankData;
class Player:public IGameObject
{
public:
	Player();
	~Player();
	bool Start() override;
	void FireBullets(float speed);
	void Move();						//移動処理
	void Turn();						//回転処理。　
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
	void SetNo(int no) {
		m_No = no;
	}
	int GetNo() {
		return m_No;
	}
private:
	float StX;											//スティックのXだぜ。
	float StY;											//スティックのYだぜ。
	SkinModel m_model;									//スキンモデル。
	SkinModel m_model2;
	wchar_t moji[256];
	GameFont m_font;
	float m_fontsize = 1.0f;							//フォントサイズ
	CVector3 m_forward = CVector3::Zero();
	CVector3 m_gunForward = CVector3::Zero();
	CVector3 m_right = CVector3::Zero();
	CVector3 m_pos = CVector3::Zero();
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CQuaternion m_rot = CQuaternion::Identity();		//回転。
	CVector3 m_scale = CVector3::One();					//スケール。
	BulletManeger* m_bulletmaneger = nullptr;
	float m_deltatime = 1.0f / 30.0f;                   //1フレームの経過時間
	//CharacterController m_charaCon;						//キャラクターコントローラーを追加。
	CharacterControllerToBox m_charaCon;					//キャラクターコントローラーを追加。
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
	int m_No = 0;
};

