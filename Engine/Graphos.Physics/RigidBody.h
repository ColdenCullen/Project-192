#ifndef __RIGID_BODY
#define __RIGID_BODY

#include "Physics.h"
#include "IComponent.h"
#include "GameObject.h"
#include "Vector3.h"

namespace Graphos
{
	namespace Physics
	{
		class RigidBody : public Graphos::Core::IComponent
		{
		public:
								RigidBody( Graphos::Core::GameObject* owner );
			
			void				Update( void );
			void				Draw( void ) { }
			void				Shutdown( void ) { }

			void				AddForce( const Graphos::Math::Vector3& force );
			void				AddForce( float x, float y, float z );

			// Drags
			float				linearDrag;
			float				angularDrag;

			// Velocities
			Graphos::Math::Vector3
								linearVelocity;
			Graphos::Math::Vector3
								angularVelocity;

			// Constraints
			Graphos::Math::Vector3
								positionConstraints;
			Graphos::Math::Vector3
								rotationConstraints;
		};
	}
}

#endif//__RIGID_BODY