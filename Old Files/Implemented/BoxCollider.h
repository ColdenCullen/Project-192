#ifndef __BOX_COLLIDER
#define __BOX_COLLIDER

#include "Collider.h"

namespace Graphos
{
	class BoxCollider : public Collider
	{
	public:
							BoxCollider( GameObject* owner );

		bool				Update( float deltaTime ) { return true; }
		void				Draw( void ) { }
		void				Shutdown( void ) { }

		const Vector3		GetFurthestPointInDirection( const Vector3& direction ) const;
		const Vector3		GetNormalOfCollision( const Vector3& otherPosition ) const;

		Vector3				size;
	};
}

#endif//__BOX_COLLIDER