#pragma once
#include "character/CharacterController.h"
class BulletManeger;
class Player:public IGameObject
{
public:
	Player();
	~Player();
	bool Start() override;
	void FireBullets();
	void Update();
	void Draw();
	void PostDraw();
private:
	SkinModel m_model;									//スキンモデル。
	wchar_t moji[256];
	GameFont m_font;
	float m_fontsize = 1.0f; //フォントサイズ
	Sprite m_sprite;
	CVector3 m_pos = CVector3::Zero();
	BulletManeger* m_bulletmaneger = nullptr;
};

