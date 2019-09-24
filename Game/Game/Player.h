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
	void Update();
	void Draw();
	void PostDraw();
private:

	void Turn();										//回転処理。　
		 
	float StX;											//スティックのXだぜ。
	float StY;											//スティックのYだぜ。

	SkinModel m_model;									//スキンモデル。
	wchar_t moji[256];
	GameFont m_font;
	float m_fontsize = 1.0f;							//フォントサイズ
	Sprite m_sprite;
	CVector3 m_pos = CVector3::Zero();
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CQuaternion m_rot = CQuaternion::Identity();		//回転。
	BulletManeger* m_bulletmaneger = nullptr;
	CharacterController m_charaCon;						//キャラクターコントローラーを追加。
};

