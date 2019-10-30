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
	Bullet* NewBullet();
	void DeleteBullet();
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
	bool kariget()
	{
		return kariflag;
	}
private:
	std::vector<Bullet*> m_bulletList;
	int m_bulletDeleteTime = 0;
	bool kariflag = false;
};

/*//BulletManeger�̃C���X�^���X���擾�B
static inline BulletManeger& G_BulletManager()
{
	return BulletManeger::Instance();
}*/
