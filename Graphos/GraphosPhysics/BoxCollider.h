#ifndef __BOX_COLLIDER
#define __BOX_COLLIDER

#include "Collider.h"

namespace Graphos
{
	namespace Physics
	{
		class BoxCollider : public Collider
		{
		public:
			BoxCollider( Graphos::Core::GameObject* owner );

			const Graphos::Math::Vector3
								GetFurthestPointInDirection( const Graphos::Math::Vector3& direction ) const;
			const Graphos::Math::Vector3
								GetNormalOfCollision( const Graphos::Math::Vector3& otherPosition ) const;

			Graphos::Math::Vector3
								size;
		};
	}
}

#endif//__BOX_COLLIDER