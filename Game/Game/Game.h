#pragma once
class Player;
class BulletManeger;
class BackGround;
class Game:public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Draw();
	/*!
	* @brief	�e�ۃ}�l�[�W�����擾�B
	*/
	BulletManeger& GetBulletManager()
	{
		return *m_bulletmaneger;
	}
private:
	Player* m_player = nullptr;
	BulletManeger* m_bulletmaneger = nullptr;
	BackGround* m_backgeound = nullptr;
	wchar_t moji[256];
	GameFont m_font;
	float m_fontsize = 1.0f; //�t�H���g�T�C�Y
	CSoundSource m_testbgm;//�e�X�gBGM
	Effekseer::Effect* m_testEffect = nullptr;//�e�X�g�G�t�F�N�g
	Effekseer::Handle m_testEffectHandle = -1;
};

