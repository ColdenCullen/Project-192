#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_

#include "Physics.h"
#include "Ingredient.h"
#include "GameObject.h"
#include "Vector3.h"

using namespace Graphos;
using namespace Graphos::Math;

namespace Graphos
{
	class Rigidbody : public Ingredient
	{
	public:
							Rigidbody( GameObject* owner );
			
		bool				Update( float deltaTime );
		void				Draw( void ) { }
		void				Shutdown( void );

		void				AddForce( const Vector3& force );
		void				AddForce( float x, float y, float z );

		// Drags
		float				linearDrag;
		float				angularDrag;

		// Velocities
		Vector3				linearVelocity;
		Vector3				angularVelocity;

		// Constraints
		Vector3				positionConstraints;
		Vector3				rotationConstraints;
	};
}

#endif//_RIGIDBODY_H_