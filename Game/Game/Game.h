#pragma once
class Player;
class TestEnemy;
class BulletManeger;
class BackGround;
class GameCamera;
class Game:public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Draw();
	/*!
	* @brief	弾丸マネージャを取得。
	*/
	BulletManeger& GetBulletManager()
	{
		return *m_bulletmaneger;
	}
private:
	Player* m_player = nullptr;
	TestEnemy* m_testenemy = nullptr;
	BulletManeger* m_bulletmaneger = nullptr;
	BackGround* m_backgeound = nullptr;
	GameCamera* m_gamecamera = nullptr;
	wchar_t moji[256];
	GameFont m_font;
	float m_fontsize = 1.0f; //フォントサイズ
	CSoundSource m_testbgm;//テストBGM
	Effekseer::Effect* m_testEffect = nullptr;//テストエフェクト
	Effekseer::Handle m_testEffectHandle = -1;
};

