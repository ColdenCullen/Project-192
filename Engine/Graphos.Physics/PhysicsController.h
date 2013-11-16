#ifndef __PHYSICS_CONTROLLER
#define __PHYSICS_CONTROLLER

#include "GameObject.h"

#include <map>
#include <vector>
#include <btBulletDynamicsCommon.h>
#include "GraphosMotionState.h"

namespace Graphos
{
	namespace Physics
	{
		class PhysicsController
		{
		public:

			struct PhysicsConfig 
			{
				gFloat				mass;
				gFloat				restitution;
				gFloat				friction;
				gFloat				rollingFriction;

				PhysicsConfig() : mass( 0.0f ), restitution( 1.0f ), friction( 0.5f ), rollingFriction( 0.4f ) {};
			};

			static void				Initialize( void );
			static void				Shutdown( void );

			// TODO: Send in collision shape
			static void				CreatePhysicsObject(	GraphosMotionState* gms, 
															const gFloat mass, 
															const gFloat restitution, 
															const gFloat friction,
															const gFloat rollingFriction );

			static PhysicsController& Get( void )
			{
				static PhysicsController instance;
				return instance;
			}

			static void StepPhysics( gFloat timeStep, gInt maxSubSteps=1, gFloat fixedTimeStep=(1.f/60.f) );

		private:
								PhysicsController( void ) { }
								PhysicsController( const PhysicsController& );

			void				operator=( const PhysicsController& );

			static btDefaultCollisionConfiguration* 
								collisionConfiguration;
			static btCollisionDispatcher* 
								dispatcher;
			static btBroadphaseInterface* 
								overlappingPairCache;
			static btSequentialImpulseConstraintSolver* 
								solver;
			static btDiscreteDynamicsWorld* 
								dynamicsWorld;

			//static vector<btRigidBody>
								
		};
	}
}

#endif//__PHYSICS_CONTROLLER
