
#include "PhysicsController.h"

#include "OutputController.h"
#include "Config.h"
#include "Vector3.h"

using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Physics;
using namespace Graphos::Utility;

void PhysicsController::Initialize( void )
{
	// TODO: Setup map

	// Set up physics logic
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new	btCollisionDispatcher(collisionConfiguration);
	overlappingPairCache = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);

	Vector3 gravity = Config::GetData<Vector3>( "physics.gravity" );

	// TODO: Fix Vector3 -> btVector3
	// Set the config gravity
	dynamicsWorld->setGravity(btVector3(gravity.x,gravity.y,gravity.z));

}

void PhysicsController::Shutdown( void )
{
	// Release map
	int i;

	//remove the rigidbodies from the dynamics world and delete them
	for (i=dynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		dynamicsWorld->removeCollisionObject( obj );
		delete obj;
	}

	/*
	//delete collision shapes
	for (int j=0;j<collisionShapes.size();j++)
	{
		btCollisionShape* shape = collisionShapes[j];
		collisionShapes[j] = 0;
		delete shape;
	}
	*/

	//delete dynamics world
	delete dynamicsWorld;

	//delete solver
	delete solver;

	//delete broadphase
	delete overlappingPairCache;

	//delete dispatcher
	delete dispatcher;

	delete collisionConfiguration;

	//next line is optional: it will be cleared by the destructor when the array goes out of scope
	//collisionShapes.clear();
}

void PhysicsController::StepPhysics( gFloat timeStep, gInt maxSubSteps, gFloat fixedTimeStep )
{
	dynamicsWorld->stepSimulation( timeStep, maxSubSteps, fixedTimeStep );
}

void PhysicsController::CreatePhysicsObject( GraphosMotionState* gms, const gFloat mass, const gFloat restitution, const gFloat friction, const gFloat rollingFriction )
{
	// 1. Create collision shape
	// Re-using the same collision shape is better for memory usage and performance
	btCollisionShape* colShape = new btBoxShape( btVector3( 1.0f, 1.0f, 1.0f ) );

	// 2. Set some properties of collision shape
	colShape->setMargin( btScalar( 0.04f ) );

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	//btScalar m = mass;
	btVector3 localInertia( 0.0f, 0.0f, 1.0f );

	colShape->calculateLocalInertia( mass, localInertia );

	// 3. Create motions state for rigid body
	//btDefaultMotionState* myMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),btVector3(0.0f, 0.0f, 0.0f)));

	// 4. Create rigid body
	btRigidBody::btRigidBodyConstructionInfo rbInfo( mass, gms, colShape, localInertia );
	rbInfo.m_angularSleepingThreshold = btScalar( 0.0f );
	rbInfo.m_linearSleepingThreshold = btScalar( 0.0f );

	btRigidBody* body = new btRigidBody( rbInfo );

	// 5. Set properties of the rigid body
	btTransform startTransform;
	startTransform.setIdentity();

	//body->setCenterOfMassTransform(startTransform);
	body->setAngularFactor( btVector3( 1.0f, 1.0f, 1.0f ) );
	body->setLinearFactor( btVector3( 1.0f, 1.0f, 0.5f ) );
	body->setDamping( 0.9f, 0.3f );
	body->setRestitution( restitution );
	body->setFriction( friction );
	body->setRollingFriction( rollingFriction );
	body->forceActivationState( DISABLE_DEACTIVATION );

	// 6. Add created rigid body to the world
	dynamicsWorld->addRigidBody( body );
}

btDefaultCollisionConfiguration* PhysicsController::collisionConfiguration;

btCollisionDispatcher* PhysicsController::dispatcher;

btBroadphaseInterface* PhysicsController::overlappingPairCache;

btSequentialImpulseConstraintSolver* PhysicsController::solver;

btDiscreteDynamicsWorld* PhysicsController::dynamicsWorld;
