#include "stdafx.h"
#include "BulletController.h"
#include "physics/CollisionAttr.h"
namespace {
	//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g
	struct SweepResultBullet : public btCollisionWorld::ConvexResultCallback
	{
		bool isHit = false;									//�Փ˃t���O�B
		CVector3 hitPos = CVector3(0.0f, -FLT_MAX, 0.0f);	//�Փ˓_�B
		CVector3 startPos = CVector3::Zero();					//���C�̎n�_�B
		CVector3 hitNormal = CVector3::Zero();				//�Փ˓_�̖@���B
		btCollisionObject* me = nullptr;					//�������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o�B
		float dist = FLT_MAX;								//�Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l�B

															//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
		virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			if (convexResult.m_hitCollisionObject == me
				|| convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character
				) {
				//�����ɏՓ˂����Bor �L�����N�^�����̃R���W�����ƏՓ˂����B
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
	//�R���W�����쐬�B
	m_radius = radius;
	m_height = height;
	m_collider.Create(radius, height);

	//���̂��������B
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_collider;
	rbInfo.mass = 0.0f;
	m_rigidBody.Create(rbInfo);
	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	//���̂̈ʒu���X�V�B
	trans.setOrigin(btVector3(position.x, position.y, position.z));
	//@todo ���Ή��Btrans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Character);
	m_rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	g_physics.AddRigidBody(m_rigidBody);

}
const CVector3& BulletController::Execute(float deltaTime, CVector3& moveSpeed)
{

}