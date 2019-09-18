#include "stdafx.h"
#include "BulletController.h"
#include "physics/CollisionAttr.h"
namespace {
	//衝突したときに呼ばれる関数オブジェクト
	struct SweepResultBullet : public btCollisionWorld::ConvexResultCallback
	{
		bool isHit = false;									//衝突フラグ。
		CVector3 hitPos = CVector3(0.0f, -FLT_MAX, 0.0f);	//衝突点。
		CVector3 startPos = CVector3::Zero();					//レイの始点。
		CVector3 hitNormal = CVector3::Zero();				//衝突点の法線。
		btCollisionObject* me = nullptr;					//自分自身。自分自身との衝突を除外するためのメンバ。
		float dist = FLT_MAX;								//衝突点までの距離。一番近い衝突点を求めるため。FLT_MAXは単精度の浮動小数点が取りうる最大の値。

															//衝突したときに呼ばれるコールバック関数。
		virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			if (convexResult.m_hitCollisionObject == me
				|| convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character
				) {
				//自分に衝突した。or キャラクタ属性のコリジョンと衝突した。
				return 0.0f;
			}
			isHit = true;
		}
	};
}


BulletController::BulletController()
{

}


BulletController::~BulletController()
{
	if (dethFlag == false)
	{
		
	}
}

void BulletController::Init(float radius,float height, const CVector3& position)
{
		m_position = position;
	//コリジョン作成。
	m_radius = radius;
	m_height = height;
	m_collider.Create(radius, height);

	//剛体を初期化。
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_collider;
	rbInfo.mass = 0.0f;
	m_rigidBody.Create(rbInfo);
	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	//剛体の位置を更新。
	trans.setOrigin(btVector3(position.x, position.y, position.z));
	//@todo 未対応。trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Character);
	m_rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	g_physics.AddRigidBody(m_rigidBody);

}
const CVector3& BulletController::Execute(float deltaTime, CVector3& moveSpeed)
{

}