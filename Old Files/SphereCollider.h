#ifndef __SPHERE_COLLIDER
#define __SPHERE_COLLIDER

#include "Collider.h"

using namespace Graphos::Content;

namespace Graphos
{
	class SphereCollider : public Collider
	{
	public:
							SphereCollider( GameObject* owner );

		bool				Update( float deltaTime ) { return true; }
		void				Draw( void ) { }
		void				Shutdown( void ) { }

		const Vector3		GetFurthestPointInDirection( const Vector3& direction ) const;
		const Vector3		GetNormalOfCollision( const Vector3& otherPosition ) const;

		float				radius;
	};
}

#endif//__SPHERE_COLLIDER