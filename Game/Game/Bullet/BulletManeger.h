#pragma once
#include "Bullet.h"
#include "TestEnemy.h"
class BulletManeger : public IGameObject
{
public:
	BulletManeger();
	~BulletManeger();
	bool Start();
	//void OnDestroy();
	Bullet* NewBullet(int collision, int number);
	void OnDestroy();
	void DeleteBullet(Bullet* bullet);
	void Update();
	void Draw();
	/// <summary>
	///�e�ۂ̔��ˏ����B
	/// </summary>
	/// <remarks>
	/// Player���e�ۂ𔭎˂��悤�Ƃ���ƌĂяo����܂��B
	/// �e�ۂ̔z�񂩂�flag��false�̗v�f�������A
	/// ���̗v�f�ɂ��ꂩ�甭�˂���e�ۂ̏����i�[����flag��true�ɂ��܂��B
	/// </remarks>
	/// <param name="p_position">�v���C���[�̍��W</param>
	/// <param name="lightDir">�v���C���[�̑O��</param>
	//void bulletShot(const CVector3 p_position, const CVector3 p_forward);
	///*!
	//*@brief	�G�Ƃ̓����蔻��B
	//*/
	//void EnemyHit(TestEnemy* enemy);
	////�s�v�ȓG�e�̍폜�B
	//void erasebullet();
	////�s�v�ȃv���C���[�̒e�̑S�폜�B
	//void erasebullet_All();

	/*!
	*@brief	�C���X�^���X�̎擾�B
	*/
	/*static BulletManeger& Instance()
	{
		static BulletManeger instance;//BulletManeger�̃C���X�^���X�𐶐��B
		return instance;
	}*/
	bool GetDamageFlag()
	{
		return m_damage;
	}
	float GetBulletDamage()
	{
		return m_bulletdamage;
	}
	void SetDamegeFlag(bool a)
	{
		m_damage = a;
	}
	void SetBulletDamage(float a)
	{
		m_bulletdamage = a;
	}
	int GetNumber()
	{
		return m_number;
	}
	int GetHitNumber()
	{
		return m_hitNumber;
	}
private:
	std::vector<Bullet*> m_bulletList;
	bool m_damage = false;
	float m_bulletdamage = 10.0f;
	int m_number = 0;
	int m_hitNumber = 0;
	prefab::CSoundSource*  m_explosionse;
	prefab::CSoundSource*  m_attsckse;
	Effekseer::Effect* m_testEffect = nullptr;//�e�X�g�G�t�F�N�g
	Effekseer::Handle m_testEffectHandle = -1;
};
