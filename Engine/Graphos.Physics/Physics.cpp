#include <math.h>

#include "Config.h"
#include "Physics.h"
#include "RigidBody.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "GameObject.h"

using namespace Graphos::Core;
using namespace Graphos::Physics;

Physics::Physics( void ) : gravity() { }

void Physics::AddCollider( Collider* col )
{
	colliders.push_back( col );
}

void Physics::Update( void )
{
	Vector3 normal;
	bool isColliding;

	// Iterate through each collider
	for( auto outsideCollider = begin( colliders ); outsideCollider != end( colliders ); ++outsideCollider )
	{
		/*
		Collider* insideTemp = GameObject::GetGameObject( "Ball" )->GetComponent<Collider>();
		Collider** insideCollider = &insideTemp;
		/*/
		// Iterate through each collider after it
		for( auto insideCollider = outsideCollider + 1; insideCollider != end( colliders ); ++insideCollider )
		//*/
		if( *outsideCollider != *insideCollider )
		{
			// Check for collisions
			if( ( *insideCollider )->Type() == Sphere && ( *outsideCollider )->Type() == Sphere )
			{
				// Check if colliding.
				isColliding = ( normal = ( ( *outsideCollider )->Owner()->transform.Position() - ( *insideCollider )->Owner()->transform.Position() ) ).Magnitude() <
					static_cast<SphereCollider*>( *outsideCollider )->radius + static_cast<SphereCollider*>( *insideCollider )->radius;
			}
			else
			{
				isColliding = CheckGJK( *insideCollider, *outsideCollider );
			}
			
			// Act on collisions;
			if( isColliding )
			{
				( *insideCollider )->Owner()->OnCollision( ( *outsideCollider )->Owner() );
				( *outsideCollider )->Owner()->OnCollision( ( *insideCollider )->Owner() );

				// Get rigid bodies involved in the collision
				RigidBody* outsideRB = ( *outsideCollider )->Owner()->GetComponent<RigidBody>();
				RigidBody* insideRB = ( *insideCollider )->Owner()->GetComponent<RigidBody>();

				// If one object is movable
				if( outsideRB == nullptr || insideRB == nullptr )
				{
					// Get pointers to the game objects
					GameObject* movableObj = outsideRB != nullptr ? ( *outsideCollider )->Owner() : ( *insideCollider )->Owner();
					GameObject* nonMovable = outsideRB == nullptr ? ( *outsideCollider )->Owner() : ( *insideCollider )->Owner();

					// Get the moveable collider as a sphere
					SphereCollider* movableCol = static_cast<SphereCollider*>( movableObj->GetComponent<Collider>() );

					// If the movable collider is a sphere
					if( movableObj->GetComponent<Collider>()->Type() == Sphere )
					{
						// Get bounce normal
						normal = nonMovable->GetComponent<Collider>()->GetNormalOfCollision( movableCol->Position() );
						
						// Get moveable velocity
						Vector3& moveVel = movableObj->GetComponent<RigidBody>()->linearVelocity;

						// If velocity and normal are in opposite directions
						if( moveVel.Dot( normal ) < 0.0f )
						{
							// Reflect velocity
							moveVel += ( normal * ( moveVel.Dot( normal ) * -2 ) );

							// Multiply by bounce values
							moveVel *= ( *insideCollider )->bounce * ( *outsideCollider )->bounce;
						}
					}
				}
				// if both are movable
				else
				{
					//TODO: Implement, or something
				}
			}
		}
	}
}

bool Physics::Initialize( void )
{
	gravity = Config::Get().GetData<Vector3>( "physics.gravity" );

	return true;
}

void Physics::Shutdown( void )
{
	gravity = Vector3();
	colliders.clear();
}

Vector3 Physics::Support( Collider* shape1, Collider* shape2, Vector3& direction )
{
	Vector3 p1 = shape1->GetFurthestPointInDirection( direction );
	Vector3 p2 = shape2->GetFurthestPointInDirection( -direction );

	p1.z = 0.0f;
	p2.z = 0.0f;

	return p1 - p2;
}

bool Physics::CheckGJK( Collider* shape1, Collider* shape2 )
{
	Vector3 direction( 1.0f, 0.0f, 0.0f );
	Simplex simplex;

	simplex.Add( Support( shape1, shape2, direction ) );

	direction = -simplex.points[ 0 ];

	while( true )
	{
		simplex.Add( Support( shape1, shape2, direction ) );

		if( simplex.GetLast().Dot( direction ) <= 0.0f )
			return false;
		else if( simplex.ContainsOrigin( direction ) )
			return true;
	}
}

/*const*/ Vector3& Physics::Simplex::GetLast( void )// const
{
	return points[ size - 1 ];
}

void Physics::Simplex::Add( const Vector3& newPoint )
{
	if( size < 4 )
		points[ size++ ] = newPoint;
}

void Physics::Simplex::Remove( const Vector3& target )
{
	bool moveBack = false;

	for( unsigned int ii = 0; ii < 4; ++ii )
	{
		if( points[ ii ] == target )
			moveBack = true;

		if( moveBack && ii < 3 )
			points[ ii ] = points[ ii + 1 ];
	}

	if( moveBack )
		--size;
}

bool Physics::Simplex::ContainsOrigin( Vector3& direction )
{
	Vector3 a = GetLast();
	Vector3 ao = -a;

	if( size == 2 )
	{
		Vector3 ab = points[ 0 ] - a;
		Vector3 abPerp = Vector3::TripleProduct( ab, ao, ab );

		direction = abPerp;
	}
	else if( size == 3 )//4 )
	{
		Vector3 b = points[ 0 ];
		Vector3 c = points[ 1 ];

		Vector3 ab = b - a;
		Vector3 ac = c - a;

		Vector3 abPerp = Vector3::TripleProduct( ac, ab, ab );
		abPerp *= abPerp.Dot( -ac );

		Vector3 acPerp = Vector3::TripleProduct( ab, ac, ac );
		acPerp *= acPerp.Dot( -ab );

		float abDot = abPerp.Dot( ao );
		float acDot = acPerp.Dot( ao );

		if( abPerp.Dot( ao ) > 0.0f )
		{
			Remove( c );
			direction = abPerp;
		}
		else if( acPerp.Dot( ao ) > 0.0f )
		{
			Remove( b );
			direction = acPerp;
		}
		else
		{
			return true;
		}
	}

	return false;
}