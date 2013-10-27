#include "BoxCollider.h"

using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Physics;

BoxCollider::BoxCollider( GameObject* owner ) : Collider( Box, owner ) { }

const Vector3 BoxCollider::GetFurthestPointInDirection( const Vector3& direction ) const
{
	const Matrix4& rotationMarix = owner->transform->RotationMatrix();

	Vector3 newDir = rotationMarix.Inverse() * direction;

	Vector3 point(
		( newDir.x > 0 ? 0.5f : -0.5f ) * size.x,
		( newDir.y > 0 ? 0.5f : -0.5f ) * size.y,
		( newDir.z > 0 ? 0.5f : -0.5f ) * size.z
	);

	return *owner->transform->Position() + ( /*rotationMarix **/ ( centerOffset + point ) );
}

const Vector3 BoxCollider::GetNormalOfCollision( const Vector3& otherPosition ) const
{
	Vector3 diff = otherPosition - Position();

	Vector3 normal;

	if( abs( diff.y ) < size.y / 2.0f )
	{
		if( diff.x > 0.0f )
			normal.x = 1.0f;
		else if( -diff.x > 0.0f )
			normal.x = -1.0f;
	}

	if( abs( diff.x ) < size.x / 2.0f )
	{
		if( diff.y > 0.0f )
			normal.y = 1.0f;
		else if( -diff.y > 0.0f )
			normal.y = -1.0f;
	}

	/*
	if( diff.z > size.z / 2.0f )
		normal.z = 1.0f;
	else if( -diff.z < size.z / 2.0f )
		normal.z = -1.0f;
	*/

	return normal.Normalize().Rotate( 0.0f, 0.0f, fmodf( owner->transform->Rotation()->z, 90.0f ) );
}