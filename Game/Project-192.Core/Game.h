#ifndef __GAME
#define __GAME

#include "GraphosGame.h"
#include "GameObjectCollection.h"

#include <btBulletDynamicsCommon.h>

namespace Project192
{
	class Game : public Graphos::Core::GraphosGame
	{
	private:
		///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
		btDefaultCollisionConfiguration* collisionConfiguration;

		///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
		btCollisionDispatcher* dispatcher;

		///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
		btBroadphaseInterface* overlappingPairCache;

		///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
		btSequentialImpulseConstraintSolver* solver;

		btDiscreteDynamicsWorld* dynamicsWorld;

		///-----initialization_end-----

		///create a few basic rigid bodies
		btCollisionShape* groundShape;

		//keep track of the shapes, we release memory at exit.
		//make sure to re-use collision shapes among rigid bodies whenever possible!
		btAlignedObjectArray<btCollisionShape*> collisionShapes;

	public:
		Graphos::Core::GameObjectCollection
							objects;
		Graphos::Core::GameObject*
							cube;

		virtual void		Initialize( void ) override;
		virtual bool		Update( void ) override;
		virtual void		Draw( void ) override;
		virtual void		Shutdown( void ) override;
	};
}

#endif//__GAME