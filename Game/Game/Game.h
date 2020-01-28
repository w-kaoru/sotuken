#pragma once
#include "level/Level.h"
class Player;
class TestEnemy;
class BulletManeger;
class BackGround;
class GameCamera;
class Score;
class GameResults;
class Sky;
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
	* @brief	�e�ۃ}�l�[�W�����擾�B
	*/
	BulletManeger& GetBulletManager()
	{
		return *m_bulletmaneger;
	}
private:
	//Player* m_player = nullptr;
	std::vector<Player*> m_playerList;		//�v���C���[�̃��X�g�B
	TestEnemy* m_testenemy = nullptr;
	BulletManeger* m_bulletmaneger = nullptr;
	BackGround* m_backgeound = nullptr;
	GameCamera* m_gamecamera = nullptr;
	Score* m_score = nullptr;
	GameResults* m_gameresults = nullptr;
	Sky* m_sky;
	wchar_t moji[256];
	GameFont m_font;
	Timer m_time;
	float m_fontsize = 1.0f; //�t�H���g�T�C�Y
	CSoundSource m_testbgm;//�e�X�gBGM
	Effekseer::Effect* m_testEffect = nullptr;//�e�X�g�G�t�F�N�g
	Effekseer::Handle m_testEffectHandle = -1;
	prefab::DirectionLight* m_directionLight = nullptr;
	CVector3 m_LigDirection = CVector3::Zero();
	int GameTime = 180;
	int	CountDownTime = 10;
	bool uuum = false;
	Level m_level;
};

