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
	void Update();
	void Draw();
	void PostDraw();
	CVector3 GetPosition()
	{
		return m_pos;
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
	CQuaternion m_rotation = { 0.0f,  0.0f, 0.0f, 1.0f };
	CVector3 test = g_camera3D.GetForward();
	float m_cameraTurnSpeed = 0.02f;
	TankData* m_tankData = nullptr;
	Sprite m_aimng;
	CVector3 m_aimingpos = CVector3::Zero();
	CVector3 m_gunpos = CVector3::Zero();
};

