#include "stdafx.h"
#include "BulletController.h"
#include "physics/CollisionAttr.h"
namespace GameEngine {
	namespace {
		//弾が衝突したときに呼ばれる関数オブジェクト
		struct SweepResultBullet : public btCollisionWorld::ConvexResultCallback
		{
			bool isHit = false;						//衝突フラグ。

			bool bulletisHit = false;          //敵弾とプレイヤーの衝突フラグ。
			int hitNumber = 0;
			int number = 0;

			btCollisionObject* me = nullptr;					//自分自身。自分自身との衝突を除外するためのメンバ。
																//衝突したときに呼ばれるコールバック関数。
			virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
			{
				if (me->getUserIndex() == enCollisionAttr_PlayerBullet&&
					convexResult.m_hitCollisionObject->getUserIndex() == 100) {
					bulletisHit = true;
					hitNumber = number;
				}
				if (me->getUserIndex() == enCollisionAttr_EnemyBullet &&
					convexResult.m_hitCollisionObject->getUserIndex() != number + enCollisionAttr_Players) {
					bulletisHit = true;
					hitNumber = number;
				}
				if (me->getUserIndex() == enCollisionAttr_PlayerBullet) {
					if (convexResult.m_hitCollisionObject->getUserIndex() >= enCollisionAttr_Players&&
						convexResult.m_hitCollisionObject->getUserIndex() != number + enCollisionAttr_Players&&
						convexResult.m_hitCollisionObject->getUserIndex() < 100) {
						bulletisHit = true;
						hitNumber = convexResult.m_hitCollisionObject->getUserIndex() - enCollisionAttr_Players;
					}
				}
				//if (me->getUserIndex() == enCollisionAttr_EnemyBullet
				//	&& convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player) {
				//	isHit = true;
				//}
				//if (me->getUserIndex() == enCollisionAttr_PlayerBullet
				//	&& convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_EnemyBullet) {
				//	isHit = true;
				//}
				if (convexResult.m_hitCollisionObject == me
					|| convexResult.m_hitCollisionObject->getUserIndex() == number + enCollisionAttr_Players
					|| convexResult.m_hitCollisionObject->getUserIndex() == 100
					|| convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_EnemyBullet) {
					//自分に衝突した。
					return 0.0f;
				}
				//ステージのどこかと衝突した。
				//衝突している。
				isHit = true;
			}
		};

	}


	BulletController::BulletController()
	{

	}


	BulletController::~BulletController()
	{
		RemoveRigidBoby();
	}

	void BulletController::Init(float radius,  const CVector3& position)
	{
		deathflag = false;
		hitFlag = false;
		m_position = position;
		//コリジョン作成。
		m_radius = radius;
		m_collider.Create(radius);

		//剛体を初期化。
		RigidBodyInfo rbInfo;
		rbInfo.collider = &m_collider;
		rbInfo.mass = 0.0f;
		m_rigidBody.Create(rbInfo);
		btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
		//剛体の位置を更新。
		trans.setOrigin(btVector3(position.x, position.y, position.z));
		//@todo 未対応。trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
		m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_PlayerBullet);
		m_rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
		g_physics.AddRigidBody(m_rigidBody);

	}
	const CVector3& BulletController::Execute(float deltaTime, CVector3& moveSpeed)
	{
		//このフレームでの衝突をはかるために初期化。
		m_bullethitFlag = false;
		hitFlag = false;
		//次の移動先となる座標を計算する。
		CVector3 nextPosition = m_position;
		//速度からこのフレームでの移動量を求める。オイラー積分。
		CVector3 addPos = moveSpeed;
		addPos *= deltaTime;
		nextPosition += addPos;
		{
			int loopCount = 0;
			while (true) {
				//現在の座標から次の移動先へ向かうベクトルを求める。
				CVector3 addPos;
				addPos.Subtract(nextPosition, m_position);

				//カプセルコライダーの中心座標 + 高さ*0.1の座標をposTmpに求める。
				CVector3 posTmp = m_position;
				posTmp.y += m_radius * 0.5f + m_radius + m_radius * 0.1f;
				//レイを作成。
				btTransform start, end;
				start.setIdentity();
				end.setIdentity();

				//始点はカプセルコライダーの中心座標 + 0.2の座標をposTmpに求める。
				start.setOrigin(btVector3(posTmp.x, posTmp.y, posTmp.z));
				//終点は次の移動先。XZ平面での衝突を調べるので、yはposTmp.yを設定する。
				end.setOrigin(btVector3(nextPosition.x, nextPosition.y, nextPosition.z));
				SweepResultBullet callback;
				callback.number = m_number;
				callback.me = m_rigidBody.GetBody();
				//衝突検出。
				g_physics.ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);
				if (callback.bulletisHit) {
					//プレイヤー弾がエネミーに当たった。
					//衝突したのでtrueを返す。
					m_bullethitFlag = true;
					m_hitpos = m_position;
					m_hitNumber = callback.hitNumber;

				}
				if (callback.isHit) {
					//当たった。
					//壁。
					//衝突したのでtrueを返す。
					m_hitpos = m_position;
					hitFlag = true;
				}
				else {
					//どことも当たらないので終わり。
					break;
				}
				loopCount++;
				if (loopCount == 5) {
					break;
				}
			}
		}
		//移動確定。
		m_position = nextPosition;
		btRigidBody* btBody = m_rigidBody.GetBody();
		//剛体を動かす。
		btBody->setActivationState(DISABLE_DEACTIVATION);
		btTransform& trans = btBody->getWorldTransform();
		//剛体の位置を更新。
		trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
		//@todo 未対応。 trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
		return m_position;
	}

	/*!
	* @brief	死亡したことを通知。
	*/
	void BulletController::RemoveRigidBoby()
	{
		if (m_rigidBody.GetBody() != nullptr) {
			g_physics.RemoveRigidBody(m_rigidBody);
		}
	}
}