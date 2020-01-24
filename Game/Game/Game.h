#pragma once
class Player;
class TestEnemy;
class BulletManeger;
class BackGround;
class GameCamera;
class Score;
class GameResults;
class Game:public IGameObject
{
public:
	Game();
	~Game();
	void InitLight();
	bool Start();
	void OnDestroy();
	void Update();
	void Draw();
	void PostDraw();
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
	Score* m_score = nullptr;
	GameResults* m_gameresults = nullptr;
	wchar_t moji[256];
	GameFont m_font;
	Timer m_time;
	float m_fontsize = 1.0f; //フォントサイズ
	CSoundSource m_testbgm;//テストBGM
	Effekseer::Effect* m_testEffect = nullptr;//テストエフェクト
	Effekseer::Handle m_testEffectHandle = -1;
	prefab::DirectionLight* m_directionLight = nullptr;
	CVector3 m_LigDirection = CVector3::Zero();
	int GameTime = 180;
	int	CountDownTime = 10;
	bool uuum = false;
};

