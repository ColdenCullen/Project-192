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

			enum CollisionShape {
				G_SPHERE,
				G_CUBE
			};

			struct PhysicsConfig 
			{
				CollisionShape		collisionShape;
				Math::Vector3		collisionDimensions;
				Math::Vector3		initialInertia;
				gFloat				mass;
				gFloat				restitution;
				gFloat				friction;
				gFloat				rollingFriction;

				PhysicsConfig() :	mass( 0.0f ),
									restitution( 1.0f ),
									friction( 0.5f ),
									rollingFriction( 0.4f ){};
			};

			static void				Initialize( void );
			static void				Shutdown( void );

			static void				CreatePhysicsObject(	GraphosMotionState* gms,
															PhysicsConfig* physConfig,
															Math::Vector3* shootVec = NULL);

			static PhysicsController& Get( void )
			{
				static PhysicsController instance;
				return instance;
			}

			static void				StepPhysics(	float timeStep,
													int maxSubSteps=1,
													float fixedTimeStep=(1.f/60.f) );




		private:
									PhysicsController( void ) { }
									PhysicsController( const PhysicsController& );

			void					operator=( const PhysicsController& );

			static btVector3		ToBulletVec3( const Math::Vector3& );

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
