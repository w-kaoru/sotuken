#pragma once
#include "level/Level.h"
class Player;
class TestEnemy;
class BulletManeger;
class BackGround;
class Score;
class GameResults;
class Sky;
class Game:public IGameObject
{
public:
	Game();
	~Game();
	void InitLight();
	bool Start()override;
	void OnDestroy()override;
	void Update()override;
	void Draw()override;
	void PostDraw(int player_num)override;
	/*!
	* @brief	�e�ۃ}�l�[�W�����擾�B
	*/
	BulletManeger& GetBulletManager()
	{
		return *m_bulletmaneger;
	}
	bool GetMoveFlag()
	{
		return MoveFlag;
	}
	//�v���C���[�̍��v�l����ݒ�B
	void SetPlayer_Totle(int p_totle)
	{
		player_total = p_totle;

		//�v���C���[�l�����K��O�ɂȂ�Ȃ��悤�ɂ���B
		if (player_total <= 0) {
			player_total = 1;
		}
		if (player_total > PLAYER_NUM) {
			player_total = PLAYER_NUM;
		}
	}

	//�v���C���[�̍��v�l����Ԃ��B
	const int Get_Player_Totle()
	{
		return player_total;
	}
private:
	std::vector<Player*> m_playerList;		//�v���C���[�̃��X�g�B
	std::vector<CVector3> m_respawnpos;
	TestEnemy* m_testenemy = nullptr;
	BulletManeger* m_bulletmaneger = nullptr;
	BackGround* m_backgeound = nullptr;
	Score* m_score = nullptr;
	GameResults* m_gameresults = nullptr;
	Sky* m_sky;
	wchar_t moji[256];
	GameFont m_font;
	Timer m_time;
	float m_fontsize = 1.0f; //�t�H���g�T�C�Y
	Effekseer::Effect* m_testEffect = nullptr;//�e�X�g�G�t�F�N�g
	Effekseer::Handle m_testEffectHandle = -1;
	prefab::DirectionLight* m_directionLight = nullptr;
	CVector3 m_LigDirection = CVector3::Zero();
	int GameTime = 20;
	int GameEndtime = 0;
	int	CountDownTime = 5;
	bool MoveFlag = false;
	bool Endflag = false;
	Level m_level;
	int player_total = 2;  //�ݒ肳�ꂽ���v�l���B
	bool m_isDeth = false;
};

