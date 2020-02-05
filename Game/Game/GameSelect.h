#pragma once
#include "TankInfo.h"

class TankData;
class GameSelect : public IGameObject
{
public:
	GameSelect();
	~GameSelect();
	bool Start();
	void Update();
	void Draw();
	void PostDraw();
	void FontDraw();
private:
	SkinModel m_tankmodel;
	SkinModel m_tankmodel2;
	SkinModel m_stagemodel;
	SkinModel m_stagemodel2;
	CVector3 m_position = {50.0f,8.0f,-50.0f};
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = { 0.2f,0.2f,0.2f };
	Sprite m_background;
	TankType m_select = TankType::pz4;
	GameFont m_font;
	wchar_t m_moji[256];
	float m_mojisize = 1.5f;	//ï∂éöÉTÉCÉY
	prefab::DirectionLight* m_directionLight = nullptr;
	CVector3 m_LigDirection = CVector3::Zero();
	int m_playercount = max(min(m_playercount, 4), 1);
	TankData* m_taknData = nullptr;
	bool deleteFlag = false;
	CSoundSource m_decisionse;
	CSoundSource m_selectbgm;
	CSoundSource m_cursorse;

};

