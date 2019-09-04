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
	SkinModel m_model;									//�X�L�����f���B
	wchar_t moji[256];
	GameFont m_font;
	float m_fontsize = 1.0f; //�t�H���g�T�C�Y
};

