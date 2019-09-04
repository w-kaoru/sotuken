#pragma once
#include "character/CharacterController.h"

class Player
{
public:
	Player();
	~Player();
	void Update();
	void Draw();
private:
	SkinModel m_model;									//スキンモデル。
	wchar_t moji[256];
	GameFont m_font;
	float m_fontsize = 1.0f; //フォントサイズ
};

