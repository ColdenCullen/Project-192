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
				float				mass;
				float				restitution;
				float				friction;
				float				rollingFriction;

				PhysicsConfig() : mass( 0.0 ), restitution( 1.0 ), friction( 0.5 ), rollingFriction( 0.4 ) {};
			};

			static void				Initialize( void );
			static void				Shutdown( void );

			// TODO: Send in collision shape
			static void				CreatePhysicsObject(	GraphosMotionState* gms, 
															const float mass, 
															const float restitution, 
															const float friction,
															const float rollingFriction );

			static PhysicsController& Get( void )
			{
				static PhysicsController instance;
				return instance;
			}

			static void StepPhysics( float timeStep, int maxSubSteps=1, float fixedTimeStep=(1.f/60.f) );

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
