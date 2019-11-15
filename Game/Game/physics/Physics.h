#pragma once

#include"PhysicsDebugDraw.h"

class RigidBody;
class CharacterController;
class PhysicsStaticObject;

class PhysicsWorld
{
	btDefaultCollisionConfiguration*		collisionConfig = nullptr;
	btCollisionDispatcher*					collisionDispatcher = nullptr;	//!<�Փˉ��������B
	btBroadphaseInterface*					overlappingPairCache = nullptr;	//!<�u���[�h�t�F�[�Y�B�Փ˔���̎}�؂�B
	btSequentialImpulseConstraintSolver*	constraintSolver = nullptr;		//!<�R���X�g���C���g�\���o�[�B�S�������̉��������B
	btDiscreteDynamicsWorld*				dynamicWorld = nullptr;			//!<���[���h�B
	PhysicsDebugDraw						m_debugDraw;					//!<�f�o�b�N�p�|���S�����\���p�N���X
public:
	~PhysicsWorld();
	void Init();
	void Update();
	void DebubDrawWorld();
	void Release();
	/*!
	* @brief	�_�C�i�~�b�N���[���h���擾�B
	*/
	btDiscreteDynamicsWorld* GetDynamicWorld()
	{
		return dynamicWorld;
	}
	/*!
	* @brief	���̂�o�^�B
	*/
	void SetDebugDrawMode(int debugMode)
	{
		//���C���[�t���[���`��̂݁B
		m_debugDraw.setDebugMode(debugMode);
	}
	void AddRigidBody(RigidBody& rb);
	/*!
	* @brief	���̂�j���B
	*/
	void RemoveRigidBody(RigidBody& rb);
	void ConvexSweepTest(
		const btConvexShape* castShape,
		const btTransform& convexFromWorld,
		const btTransform& convexToWorld,
		btCollisionWorld::ConvexResultCallback& resultCallback,
		btScalar allowedCcdPenetration = 0.0f
	)
	{
		dynamicWorld->convexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
	}
	//void ContactText(
	//	btCollisionObject* colObj, 
	//	btCollisionWorld::ContactResultCallback& resultCallback
	//)
	//{
	//	dynamicWorld->contactTest(colObj, resultCallback);
	//}

	void ContactTest(
		btCollisionObject* colObj,
		std::function<void(const btCollisionObject& contactCollisionObject)> cb
	);
	void ContactTest(
		RigidBody& rb,
		std::function<void(const btCollisionObject& contactCollisionObject)> cb
	);
	void ContactTest(
		CharacterController& charaCon,
		std::function<void(const btCollisionObject& contactCollisionObject)> cb
	);
	void ContactTest(
		PhysicsStaticObject& physicsstaticobject,
		std::function<void(const btCollisionObject& contactCollisionObject)> cb
	);
};

extern PhysicsWorld g_physics;


