#pragma once
#include "TankInfo.h"

//class TankData;
class StageData;
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
	SkinModel m_tankmodel;                             //プレビュー用の戦車モデルその1。
	SkinModel m_tankmodel2;                            //プレビュー用の戦車モデルその2。
	SkinModel m_stagemodel;
	SkinModel m_stagemodel2;
	CVector3 m_position = {50.0f,8.0f,-50.0f};
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = { 0.2f,0.2f,0.2f };
	CVector3 m_stgaescale = { 0.05f,0.05f,0.05f };
	Sprite m_background;                               //セレクト画面の背景画像。
	TankType m_select = TankType::nonType;
	GameFont m_font;
	wchar_t m_moji[256];
	float m_mojisize = 1.5f;	//文字サイズ
	prefab::DirectionLight* m_directionLight = nullptr;
	CVector3 m_LigDirection = CVector3::Zero();
	//TankData* m_taknData = nullptr;
	bool deleteFlag = false;
	prefab::CSoundSource* m_decisionse = nullptr;
	prefab::CSoundSource* m_selectbgm = nullptr;
	prefab::CSoundSource* m_cursorse = nullptr;
	int m_playernum = 1;
	Stagenum m_gameselect = ninnzuu;
	StageData* m_stagedata = nullptr;
	int m_count = 0;
};

