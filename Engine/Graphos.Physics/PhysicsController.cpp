
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
	// TODO: Setup map for collision shape reuse

	// Set up physics logic
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher( collisionConfiguration );
	overlappingPairCache = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(	dispatcher,
													overlappingPairCache,
													solver,
													collisionConfiguration );

	// Pull gravity config and set the dynamics world to that setting
	Vector3 gravity = Config::GetData<Vector3>( "physics.gravity" );
	dynamicsWorld->setGravity( ToBulletVec3( gravity ) );

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

// Steps the physics simulation
void PhysicsController::StepPhysics( float timeStep, int maxSubSteps, float fixedTimeStep )
{
	dynamicsWorld->stepSimulation( timeStep, maxSubSteps, fixedTimeStep );
}


// Sends Physics Controller construction information to construct a rigid body
// @param gms A GraphosMotionState to link the render and physics objects
// @param physConfig A struct containing the construction information
void PhysicsController::CreatePhysicsObject( GraphosMotionState* gms, PhysicsConfig* physConfig, Vector3* shootVec )
{

	// Set collision Shape
	btCollisionShape* colShape = nullptr;
	btVector3 colDimensions = ToBulletVec3( physConfig->collisionDimensions );

	
	//printf("dimension x: %f\n", colDimensions.x() );

	// Determine collision shape
	switch( physConfig->collisionShape )
	{
		case G_CUBE:
			colShape = new btBoxShape( colDimensions );
			//static_cast<btBoxShape *>(colShape)->setLocalScaling( colDimensions );
			break;
		case G_SPHERE:
			colShape = new btSphereShape( colDimensions.x() );
			//static_cast<btSphereShape *>(colShape)->setUnscaledRadius( colDimensions.getX() );
			break;
		default:
			colShape = new btBoxShape( colDimensions );
			//static_cast<btBoxShape *>(colShape)->setLocalScaling( colDimensions );
			break;
	}



	//
	// Set properties of collision shape
	//
	colShape->setMargin( btScalar( 0.04f ) );


	//
	// Set inertia
	//
	btVector3 localInertia(		physConfig->initialInertia.x,
								physConfig->initialInertia.y, 
								physConfig->initialInertia.z );
	colShape->calculateLocalInertia( physConfig->mass, localInertia );



	// 3. Create motions state for rigid body
	//btDefaultMotionState* myMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),btVector3(0.0f, 0.0f, 0.0f)));



	// 4. Create rigid body
	btRigidBody::btRigidBodyConstructionInfo rbInfo( physConfig->mass, gms, colShape, localInertia );
	rbInfo.m_angularSleepingThreshold = btScalar( 0.0f );
	rbInfo.m_linearSleepingThreshold = btScalar( 0.0f );

	btRigidBody* body = new btRigidBody( rbInfo );

	
	printf("size x: %f\n", static_cast<btBoxShape *>(colShape)->getHalfExtentsWithMargin().x() );
	printf("size y: %f\n", static_cast<btBoxShape *>(colShape)->getHalfExtentsWithMargin().y() );
	printf("size z: %f\n", static_cast<btBoxShape *>(colShape)->getHalfExtentsWithMargin().z() );
	
	printf("default box x pos: %f\n", body->getCenterOfMassPosition().x() );
	printf("default box y pos: %f\n", body->getCenterOfMassPosition().y() );
	printf("default box z pos: %f\n", body->getCenterOfMassPosition().z() );
	
	

	// 5. Set properties of the rigid body
	//btTransform startTransform;
	//startTransform.setIdentity();

	//body->setCenterOfMassTransform(startTransform);
	body->setAngularFactor( btVector3( 1.0f, 1.0f, 1.0f ) );
	body->setLinearFactor( btVector3( 1.0f, 1.0f, 0.5f ) );
	body->setDamping( 0.9f, 0.3f );
	body->setRestitution( physConfig->restitution );
	body->setFriction( physConfig->friction );
	body->setRollingFriction( physConfig->rollingFriction );
	body->forceActivationState( DISABLE_DEACTIVATION );

	//body->applyCentralForce( btVector3( 0, 2000, 0 ) );

	// 6. Add created rigid body to the world
	dynamicsWorld->addRigidBody( body );

	if( shootVec )
	{
		btVector3 forceDir = ToBulletVec3( *shootVec );
		body->applyCentralForce( forceDir );
	}

}

// Conversion from Graphos::Math::Vector3 to btVector3
// @param a Const reference to Vector3
// @return A new btVector3 containing the same data
btVector3 PhysicsController::ToBulletVec3( const Vector3& a )
{
	return btVector3( a.x, a.y, a.z );
}

btDefaultCollisionConfiguration* PhysicsController::collisionConfiguration;

btCollisionDispatcher* PhysicsController::dispatcher;

btBroadphaseInterface* PhysicsController::overlappingPairCache;

btSequentialImpulseConstraintSolver* PhysicsController::solver;

btDiscreteDynamicsWorld* PhysicsController::dynamicsWorld;
