#ifndef __COLLIDER
#define __COLLIDER

#include "Component.h"
#include "Vector3.h"
#include "GameObject.h"

namespace Graphos
{
	namespace Physics
	{
		// Enum for what type of collider this is
		enum ColliderType : unsigned char { Sphere, Box };

		class Collider : public Graphos::Core::Component
		{
		public:
			virtual bool		Update( void ) { return true; }
			virtual void		Draw( void ) { }
			virtual void		Shutdown( void ) { }

			const ColliderType	Type( void ) const	{ return type; }
			const Graphos::Math::Vector3
								Position( void ) const { return owner->transform.Position() + centerOffset; }
			virtual const Graphos::Math::Vector3
								GetFurthestPointInDirection( const Graphos::Math::Vector3& direction ) const = 0;
			virtual const Graphos::Math::Vector3
								GetNormalOfCollision( const Graphos::Math::Vector3& otherPosition ) const = 0;

			Graphos::Math::Vector3
				centerOffset;
			float				bounce;

			//friend class		Physics;

		protected:
								Collider( ColliderType colliderType, Graphos::Core::GameObject* owner );

		private:
			ColliderType		type;
		};
	}
}

#endif//__COLLIDER