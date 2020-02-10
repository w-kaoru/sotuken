#pragma once
#include "TankInfo.h"

class TankData;
class GameSelect : public IGameObject
{
public:
	GameSelect();
	~GameSelect();
	bool Start();
	void OnDestroy()override;
	void Update();
	void Draw();
	void PostDraw();
	void FontDraw();
private:
	SkinModel m_tankmodel;                             //�v���r���[�p�̐�ԃ��f������1�B
	SkinModel m_tankmodel2;                            //�v���r���[�p�̐�ԃ��f������2�B
	SkinModel m_stagemodel;
	SkinModel m_stagemodel2;
	CVector3 m_position = {50.0f,8.0f,-50.0f};
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = { 0.2f,0.2f,0.2f };
	Sprite m_background;                               //�Z���N�g��ʂ̔w�i�摜�B
	TankType m_select = TankType::ninzuu;
	GameFont m_font;
	wchar_t m_moji[256];
	float m_mojisize = 1.5f;	//�����T�C�Y
	prefab::DirectionLight* m_directionLight = nullptr;
	CVector3 m_LigDirection = CVector3::Zero();
	int m_playercount = max(min(m_playercount, 4), 1);
	TankData* m_taknData = nullptr;
	bool deleteFlag = false;
	prefab::CSoundSource* m_decisionse = nullptr;
	prefab::CSoundSource* m_selectbgm = nullptr;
	prefab::CSoundSource* m_cursorse = nullptr;
	int m_playernum = 1;

};

