#include "SphereCollider.h"

using namespace Graphos::Math;
using namespace Graphos::Physics;

SphereCollider::SphereCollider( Graphos::Core::GameObject* owner ) : Collider( Sphere, owner ) { }

const Vector3 SphereCollider::GetFurthestPointInDirection( const Vector3& direction ) const
{
	return owner->transform.Position() + ( /*owner->transform.RotationMatrix() **/ centerOffset ) + ( direction.Normalize() * radius );
}

const Vector3 SphereCollider::GetNormalOfCollision( const Vector3& otherPosition ) const
{
	return ( otherPosition - Position() ).Normalize();
}