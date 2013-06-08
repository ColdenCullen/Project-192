#include "Rigidbody.h"

using namespace Graphos;

Rigidbody::Rigidbody( GameObject* owner ) : Ingredient( owner ), linearVelocity(), angularVelocity(), linearDrag( 0.0f ), angularDrag( 0.0f ), positionConstraints(), rotationConstraints() { }

bool Rigidbody::Update( float deltaTime )
{
	// Update velocities with drag
	//linearVelocity *= ( ( 1 - linearDrag ) * deltaTime );
	//angularVelocity *= ( ( 1 - angularDrag ) * deltaTime );
	
	// Check constraints
	if( positionConstraints.Magnitude() > 0.0f )
	{
		linearVelocity.x *= positionConstraints.x;
		linearVelocity.y *= positionConstraints.y;
		linearVelocity.z *= positionConstraints.z;
	}
	
	if( rotationConstraints.Magnitude() > 0.0f )
	{
		angularVelocity.x *= rotationConstraints.x;
		angularVelocity.y *= rotationConstraints.y;
		angularVelocity.z *= rotationConstraints.z;
	}

	// Add gravity
	linearVelocity += Physics::Get().gravity * deltaTime;

	// Update object
	owner->transform.Translate( linearVelocity * deltaTime );
	owner->transform.Rotate( angularVelocity * deltaTime );

	return true;
}

void Rigidbody::Shutdown( void )
{

}

void Rigidbody::AddForce( const Vector3& force )
{
	linearVelocity += force;
}

void Rigidbody::AddForce( float x, float y, float z )
{
	linearVelocity.x += x;
	linearVelocity.y += y;
	linearVelocity.z += z;
}