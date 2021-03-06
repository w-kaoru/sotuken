#pragma once
class TankData;
class BulletTypeChange;
class UI:public IGameObject
{
public:
	UI();
	~UI();
	bool Start()override;
	void Update()override;
	void PostDraw()override;
	void PostDraw(int player_num)override;
	void SetAimingScale(CVector3 scale)
	{
		m_aimingScale = scale;
	}
	void SetHP(float hp)
	{
		m_hp = hp;
	}
	void SetNumber(int num) {
		m_number = num;
	}
	void SetBulletChange(BulletTypeChange* change) 
	{
		m_bulletChange = change;
	}


private:
	Sprite m_aiming;
	Sprite m_bulletsprite;
	CVector3 m_aimingpos = CVector3::Zero();
	Sprite m_playerhp;
	wchar_t m_moji[256];
	GameFont m_font;
	float m_fontsize = 0.8f;							//フォントサイズ
	//TankData* m_tankData = nullptr;
	float m_hp = 0.0f;
	CVector3 m_aimingScale = CVector3::Zero();
	int m_number = 0;//UI所持のプレイヤー番号。
	int player_total = 1;//プレイヤーの合計。
	BulletTypeChange* m_bulletChange = nullptr;
};

