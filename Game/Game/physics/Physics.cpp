#include "stdafx.h"
#include "physics/Physics.h"
#include"../character/CharacterController.h"
#include"PhysicsStaticObject.h"
#include "Physics/RigidBody.h"


PhysicsWorld g_physics;

struct MyContactResultCallback : public btCollisionWorld::ContactResultCallback {
	using ContantTestCallback = std::function<void(const btCollisionObject& contactCollisionObject)>;
	ContantTestCallback  m_cb;
	btCollisionObject* m_me = nullptr;
	virtual	btScalar	addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1) override
	{
		if (m_me == colObj0Wrap->getCollisionObject()) {
			m_cb(*colObj1Wrap->getCollisionObject());
		}
		return 0.0f;
	}
};

PhysicsWorld::~PhysicsWorld()
{
	Release();
}
void PhysicsWorld::Release()
{
	delete dynamicWorld;
	delete constraintSolver;
	delete overlappingPairCache;
	delete collisionDispatcher;
	delete collisionConfig;

	dynamicWorld = nullptr;
	constraintSolver = nullptr;
	overlappingPairCache = nullptr;
	collisionDispatcher = nullptr;
	collisionConfig = nullptr;
}
void PhysicsWorld::Init()
{
	Release();
	//�����G���W�����������B
	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	collisionConfig = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	collisionDispatcher = new	btCollisionDispatcher(collisionConfig);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	constraintSolver = new btSequentialImpulseConstraintSolver;

	dynamicWorld = new btDiscreteDynamicsWorld(
		collisionDispatcher,
		overlappingPairCache,
		constraintSolver,
		collisionConfig
		);

	dynamicWorld->setGravity(btVector3(0, -10, 0));
	m_debugDraw.Init();
	dynamicWorld->setDebugDrawer(&m_debugDraw);
}
void PhysicsWorld::Update()
{
	dynamicWorld->stepSimulation(1.0f/60.0f);
}
void PhysicsWorld::DebubDrawWorld()
{
	m_debugDraw.BeginDraw();

	dynamicWorld->debugDrawWorld();

	m_debugDraw.EndDraw();
}
void PhysicsWorld::AddRigidBody(RigidBody& rb)
{
	dynamicWorld->addRigidBody(rb.GetBody());
}
void PhysicsWorld::RemoveRigidBody(RigidBody& rb)
{
	dynamicWorld->removeRigidBody(rb.GetBody());
}

void PhysicsWorld::ContactTest(
	btCollisionObject* colObj,
	std::function<void(const btCollisionObject& contactCollisionObject)> cb
)
{
	MyContactResultCallback myContactResultCallback;
	myContactResultCallback.m_cb = cb;
	myContactResultCallback.m_me = colObj;
	dynamicWorld->contactTest(colObj, myContactResultCallback);
}
void PhysicsWorld::ContactTest(
	RigidBody& rb,
	std::function<void(const btCollisionObject& contactCollisionObject)> cb
)
{
	ContactTest(rb.GetBody(), cb);
}
void PhysicsWorld::ContactTest(
	CharacterController& charaCon,
	std::function<void(const btCollisionObject& contactCollisionObject)> cb
)
{
	ContactTest(*charaCon.GetRigidBody(), cb);
}
void PhysicsWorld::ContactTest(
	PhysicsStaticObject& physicsstaticobject,
	std::function<void(const btCollisionObject& contactCollisionObject)> cb
)
{
	ContactTest(*physicsstaticobject.GetRigidBody(), cb);
}