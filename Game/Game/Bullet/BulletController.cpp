#include "stdafx.h"
#include "BulletController.h"
#include "physics/CollisionAttr.h"
namespace GameEngine {
	namespace {
		//�e���Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g
		struct SweepResultBullet : public btCollisionWorld::ConvexResultCallback
		{
			bool isHit = false;						//�Փ˃t���O�B
			bool E_bulletisHit = false;					//�G�e�ƃv���C���[�̏Փ˃t���O�B
			btCollisionObject* me = nullptr;					//�������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o�B
																//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
			virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
			{
				if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Enemy) {
					E_bulletisHit = true;
				}
				if (me->getUserIndex() == enCollisionAttr_EnemyBullet
					&& convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player) {
					isHit = true;
				}
				if (me->getUserIndex() == enCollisionAttr_PlayerBullet
					&& convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_EnemyBullet) {
					isHit = true;
				}
				if (convexResult.m_hitCollisionObject == me
					|| convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player
					|| convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Enemy
					|| convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_EnemyBullet) {
					//�����ɏՓ˂����B
					return 0.0f;
				}
				//�X�e�[�W�̂ǂ����ƏՓ˂����B
				//�Փ˂��Ă���B
				isHit = true;
			}
		};
	}


	BulletController::BulletController()
	{

	}


	BulletController::~BulletController()
	{
		if (deathflag == false)
		{
			RemoveRigidBoby();
		}
	}

	void BulletController::Init(float radius,  const CVector3& position)
	{
		deathflag = false;
		hitFlag = false;
		m_position = position;
		//�R���W�����쐬�B
		m_radius = radius;
		m_collider.Create(radius);

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
		//���̃t���[���ł̏Փ˂��͂��邽�߂ɏ������B
		E_bullethitFlag = false;
		hitFlag = false;
		//���̈ړ���ƂȂ���W���v�Z����B
		CVector3 nextPosition = m_position;
		//���x���炱�̃t���[���ł̈ړ��ʂ����߂�B�I�C���[�ϕ��B
		CVector3 addPos = moveSpeed;
		addPos *= deltaTime;
		nextPosition += addPos;
		{
			int loopCount = 0;
			while (true) {
				//���݂̍��W���玟�̈ړ���֌������x�N�g�������߂�B
				CVector3 addPos;
				addPos.Subtract(nextPosition, m_position);

				//�J�v�Z���R���C�_�[�̒��S���W + ����*0.1�̍��W��posTmp�ɋ��߂�B
				CVector3 posTmp = m_position;
				posTmp.y += m_radius * 0.5f + m_radius + m_radius * 0.1f;
				//���C���쐬�B
				btTransform start, end;
				start.setIdentity();
				end.setIdentity();

				//�n�_�̓J�v�Z���R���C�_�[�̒��S���W + 0.2�̍��W��posTmp�ɋ��߂�B
				start.setOrigin(btVector3(posTmp.x, posTmp.y, posTmp.z));
				//�I�_�͎��̈ړ���BXZ���ʂł̏Փ˂𒲂ׂ�̂ŁAy��posTmp.y��ݒ肷��B
				end.setOrigin(btVector3(nextPosition.x, nextPosition.y, nextPosition.z));
				SweepResultBullet callback;
				callback.me = m_rigidBody.GetBody();
				//�Փˌ��o�B
				g_physics.ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);
				if (callback.E_bulletisHit) {
					//�G�e���v���C���[�ɓ��������B
					//�Փ˂����̂�true��Ԃ��B
					E_bullethitFlag = true;
				}
				if (callback.isHit) {
					//���������B
					//�ǁB
					//�Փ˂����̂�true��Ԃ��B
					hitFlag = true;
				}
				else {
					//�ǂ��Ƃ�������Ȃ��̂ŏI���B
					break;
				}
				loopCount++;
				if (loopCount == 5) {
					break;
				}
			}
		}
		//�ړ��m��B
		m_position = nextPosition;
		btRigidBody* btBody = m_rigidBody.GetBody();
		//���̂𓮂����B
		btBody->setActivationState(DISABLE_DEACTIVATION);
		btTransform& trans = btBody->getWorldTransform();
		//���̂̈ʒu���X�V�B
		trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
		//@todo ���Ή��B trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
		return m_position;
	}

	/*!
	* @brief	���S�������Ƃ�ʒm�B
	*/
	void BulletController::RemoveRigidBoby()
	{
		//if (m_rigidBody.GetBody() != nullptr) {
			g_physics.RemoveRigidBody(m_rigidBody);
		//}
			deathflag = true;
	}
}