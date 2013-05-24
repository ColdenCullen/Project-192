#ifndef __COLLIDER
#define __COLLIDER

#include "Ingredient.h"
#include "Vector3.h"
#include "GameObject.h"

using namespace Graphos::Math;
using namespace Graphos::Content;

namespace Graphos
{
	// Enum for what type of collider this is
	enum ColliderType : unsigned char { Sphere, Box };

	class Collider : public Ingredient
	{
	public:
		virtual bool		Update( float deltaTime ) { return true; }
		virtual void		Draw( void ) { }
		virtual void		Shutdown( void ) { }

		const ColliderType	Type( void ) const	{ return type; }
		const Vector3		Position( void ) const { return owner->transform.Position() + centerOffset; }
		virtual const Vector3
							GetFurthestPointInDirection( const Vector3& direction ) const = 0;
		virtual const Vector3
							GetNormalOfCollision( const Vector3& otherPosition ) const = 0;

		Vector3				centerOffset;
		float				bounce;

		//friend class		Physics;

	protected:
							Collider( ColliderType colliderType, GameObject* owner );

	private:
		ColliderType		type;
	};
}

#endif//__COLLIDER