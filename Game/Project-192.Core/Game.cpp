#include "Game.h"
#include "Input.h"
#include "TimeController.h"
#include "ShaderController.h"
#include "WindowController.h"
#include "Matrix4.h"

using namespace Project192;
using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Graphics;

void Game::Initialize( void )
{
	objects.LoadObjects( "" );
	cube = objects.GetObjectByName( "Cube" );
	CurrentState = GameState::Game;


	
	int i;
	///-----initialization_start-----

	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	dispatcher = new	btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0,-10,0));

	///-----initialization_end-----

	///create a few basic rigid bodies
	groundShape = new btBoxShape(btVector3(btScalar(50.),btScalar(50.),btScalar(50.)));

	collisionShapes.push_back(groundShape);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0,-56,0));

	{
		btScalar mass(0.);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0,0,0);
		if (isDynamic)
			groundShape->calculateLocalInertia(mass,localInertia);

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,groundShape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		//add the body to the dynamics world
		dynamicsWorld->addRigidBody(body);
	}


	{
		//create a dynamic rigidbody

		//btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
		btCollisionShape* colShape = new btSphereShape(btScalar(1.));
		collisionShapes.push_back(colShape);

		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();

		btScalar	mass(1.f);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0,0,0);
		if (isDynamic)
			colShape->calculateLocalInertia(mass,localInertia);

			startTransform.setOrigin(btVector3(2,10,0));
		
			//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
			btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,colShape,localInertia);
			btRigidBody* body = new btRigidBody(rbInfo);

			dynamicsWorld->addRigidBody(body);
	}



/// Do some simulation

	/*
	///-----stepsimulation_start-----
	for (i=0;i<100;i++)
	{
		dynamicsWorld->stepSimulation(1.f/60.f,10);
		
		//print positions of all objects
		for (int j=dynamicsWorld->getNumCollisionObjects()-1; j>=0 ;j--)
		{
			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState())
			{
				btTransform trans;
				body->getMotionState()->getWorldTransform(trans);
				printf("world pos = %f,%f,%f\n",float(trans.getOrigin().getX()),float(trans.getOrigin().getY()),float(trans.getOrigin().getZ()));
			}
		}
	}

	///-----stepsimulation_end-----
	*/
	
}

bool Game::Update( void )
{
	switch( CurrentState )
	{
	case GameState::Menu:
		{
			ui->Update();

			break;
		}
	case GameState::Game:
		{
			dynamicsWorld->stepSimulation(1.f/60.f,10);

			objects.CallFunction( &GameObject::Update );

			float rotation = 5.0f * Time::GetDeltaTime();

			cube->transform->Rotate( rotation, rotation, 0.0f );

			break;
		}
	}

	if( ISingleton<Input>::Get().IsKeyDown( VK_ESCAPE ) )
		Exit();

	if( ISingleton<Input>::Get().IsKeyDown( VK_F5 ) )
		Reset();

	return true;
}

void Game::Draw( void )
{
	switch( CurrentState )
	{
	case GameState::Menu:
		{
			ui->Draw();

			break;
		}
	case GameState::Game:
		{
			ISingleton<ShaderController>::Get().GetShader( "light" )->SetViewMatrix( camera->GetViewMatrix() );
			ISingleton<ShaderController>::Get().GetShader( "light" )->SetProjectionMatrix( WindowController::Get().PerspectiveMatrix() );

			//camera->Draw();
			objects.CallFunction( &GameObject::Draw );

			break;
		}
	}
}

void Game::Shutdown( void )
{
	objects.ClearObjects();

	//cleanup in the reverse order of creation/initialization
	
	///-----cleanup_start-----
	
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

	//delete collision shapes
	for (int j=0;j<collisionShapes.size();j++)
	{
		btCollisionShape* shape = collisionShapes[j];
		collisionShapes[j] = 0;
		delete shape;
	}

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
	collisionShapes.clear();

	///-----cleanup_end-----
	
}