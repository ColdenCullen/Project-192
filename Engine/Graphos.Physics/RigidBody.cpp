#include "RigidBody.h"
#include "TimeController.h"

using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Physics;

RigidBody::RigidBody( GameObject* owner ) : IComponent( owner ), linearVelocity(), angularVelocity(), linearDrag( 0.0f ), angularDrag( 0.0f ), positionConstraints(), rotationConstraints() { }

void RigidBody::Update( void )
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

	float deltaTime = Time::GetDeltaTime();

	// Add gravity
	linearVelocity += Physics::gravity * deltaTime;

	// Update object
	owner->transform->Translate( linearVelocity * deltaTime );
	owner->transform->Rotate( angularVelocity * deltaTime );
}

void RigidBody::AddForce( const Vector3& force )
{
	linearVelocity += force;
}

void RigidBody::AddForce( float x, float y, float z )
{
	linearVelocity.x += x;
	linearVelocity.y += y;
	linearVelocity.z += z;
}