#pragma once
#include "character/CharacterController.h"

class Player:public IGameObject
{
public:
	Player();
	~Player();
	bool Start() override;
	void Update();
	void Draw();
	void PostDraw();
private:
	SkinModel m_model;									//スキンモデル。
	wchar_t moji[256];
	GameFont m_font;
	float m_fontsize = 1.0f; //フォントサイズ
	Sprite m_sprite;
};

