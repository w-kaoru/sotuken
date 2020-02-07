#pragma once
#include "character/CharacterController.h"
#include "character/CharacterControllerToBox.h"
class BulletManeger;
class TankData;
class Game;
class GameCamera;
class UI;
class BulletTypeChange;
class Player:public IGameObject
{
public:
	Player();
	~Player();
	bool Start() override;
	void OnDestroy()override;
	void FireBullets(float speed);
	void Move();						//移動処理
	void Turn();						//回転処理
	void Update()override;
	//非ゲーム時の描画。
	void Draw()override;
	//ゲーム時の分割描画。
	void Draw(int player_num)override;
	CVector3 GetPosition()
	{
		return m_pos;
	}
	void SetPosition(CVector3 pos)
	{
		m_pos = pos;
		m_charaCon.SetPosition(m_pos);
	}
	CVector3 GetForward()
	{
		return m_forward;
	}
	//プレイヤーの死亡フラグを取得(trueで死亡)
	bool GetPlayerDeth()
	{
		return playerdeth;
	}
	/*float GetCameraSpeed()
	{
		return m_cameraTurnSpeed;
	}*/
	void SetNumber(int num) {
		m_number = num;
	}
	int GetNumber() {
		return m_number;
	}
	void SetMoveFlag(bool move)
	{
		moveflag = move;
	}
	BulletTypeChange* GetBulletChange() {
		return m_bulletChange;
	}
private:
	float StX;											//スティックのXだぜ。
	float StY;											//スティックのYだぜ。
	SkinModel m_model;									//スキンモデル。
	SkinModel m_model2;
	Game* m_game = nullptr;
	GameCamera* m_gamecamera = nullptr;
	CVector3 m_forward = CVector3::Zero();
	CVector3 m_gunForward = CVector3::Zero();
	CVector3 m_right = CVector3::Zero();
	CVector3 m_pos = CVector3::Zero();
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度。
	CQuaternion m_rot = CQuaternion::Identity();		//回転。
	CVector3 m_scale = CVector3::One();					//スケール。
	BulletManeger* m_bulletmaneger = nullptr;
	float m_deltatime = 1.0f / 30.0f;                   //1フレームの経過時間
	CharacterControllerToBox m_charaCon;				//キャラクターコントローラーを追加。
	float m_playerHP = 100.0f;                          //プレイヤーのHP。
	Sprite m_playerhp;                                  //プレイヤーのHPを表示するスプライト。
	bool playerdeth = false;                            //プレイヤーの死亡フラグ(trueで死亡)。
	int m_timier = 0;
	CQuaternion m_rotation = CQuaternion::Identity();
	TankData* m_tankData = nullptr;
	bool moveflag = false;
	int m_number = 0;                                   //プレイヤーのナンバー（何番目のプレイヤーか？）
	CVector3 m_aimingSpriteScale = CVector3::One();
	UI* m_ui = nullptr;
	BulletTypeChange* m_bulletChange = nullptr;
	float m_downSpeed = 1.0f;
	Effekseer::Effect* m_smokeEffect = nullptr;//テストエフェクト
	Effekseer::Handle m_smokeEffectHandle = -1;
	prefab::CSoundSource* m_movese;
};

