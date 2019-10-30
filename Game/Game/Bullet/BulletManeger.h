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
	///弾丸の発射処理。
	/// </summary>
	/// <remarks>
	/// Playerが弾丸を発射しようとすると呼び出されます。
	/// 弾丸の配列からflagがfalseの要素を見つけ、
	/// その要素にこれから発射する弾丸の情報を格納してflagをtrueにします。
	/// </remarks>
	/// <param name="p_position">プレイヤーの座標</param>
	/// <param name="lightDir">プレイヤーの前方</param>
	//void bulletShot(const CVector3 p_position, const CVector3 p_forward);
	///*!
	//*@brief	敵との当たり判定。
	//*/
	//void EnemyHit(TestEnemy* enemy);
	////不要な敵弾の削除。
	//void erasebullet();
	////不要なプレイヤーの弾の全削除。
	//void erasebullet_All();

	/*!
	*@brief	インスタンスの取得。
	*/
	/*static BulletManeger& Instance()
	{
		static BulletManeger instance;//BulletManegerのインスタンスを生成。
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

/*//BulletManegerのインスタンスを取得。
static inline BulletManeger& G_BulletManager()
{
	return BulletManeger::Instance();
}*/
