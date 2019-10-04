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
	void Move();						//移動処理
	void Turn();						//回転処理。　
	void Update();
	void Draw();
	void PostDraw();
	CVector3 GetPosition()
	{
		return m_pos;
	}
private:
		 

	float StX;											//スティックのXだぜ。
	float StY;											//スティックのYだぜ。
	SkinModel m_model;									//スキンモデル。
	wchar_t moji[256];
	GameFont m_font;
	float m_fontsize = 1.0f;							//フォントサイズ
	Sprite m_sprite;
	CVector3 m_forward = CVector3::Zero();
	CVector3 m_pos = CVector3::Zero();
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CQuaternion m_rot = CQuaternion::Identity();		//回転。
	CVector3 m_scale = CVector3::One();					//スケール。
	BulletManeger* m_bulletmaneger = nullptr;
	float m_deltatime = 1.0f / 30.0f;                   //1フレームの経過時間
	CharacterController m_charaCon;						//キャラクターコントローラーを追加。
};

