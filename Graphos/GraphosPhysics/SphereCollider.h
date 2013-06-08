#ifndef __SPHERE_COLLIDER
#define __SPHERE_COLLIDER

#include "Collider.h"

namespace Graphos
{
	namespace Physics
	{
		class SphereCollider : public Collider
		{
		public:
			SphereCollider( Graphos::Core::GameObject* owner );

			const Graphos::Math::Vector3
								GetFurthestPointInDirection( const Graphos::Math::Vector3& direction ) const;
			const Graphos::Math::Vector3
								GetNormalOfCollision( const Graphos::Math::Vector3& otherPosition ) const;

			float				radius;
		};
	}
}

#endif//__SPHERE_COLLIDER