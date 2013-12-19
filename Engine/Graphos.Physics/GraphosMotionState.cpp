#include "GraphosMotionState.h"
#include "GameObject.h"

using namespace Graphos::Core;
using namespace Graphos::Physics;

GraphosMotionState::GraphosMotionState( GameObject* owner ) : IComponent( owner ) {}

void Graphos::Physics::GraphosMotionState::Shutdown( void )
{
}

void Graphos::Physics::GraphosMotionState::getWorldTransform( btTransform& worldTrans ) const
{
	// No need to scale here!

	// Send rotation
	worldTrans.setRotation( *owner->transform->Rotation() );

	// Send position
	Math::Vector3 pos = *owner->transform->Position();
	worldTrans.setOrigin( btVector3( pos.x, pos.y, pos.z ) );

}

void Graphos::Physics::GraphosMotionState::setWorldTransform( const btTransform& worldTrans )
{
	// No need to scale here!

	// Save rotations
	owner->transform->RotateTo(worldTrans.getRotation());

	// Save positions
	owner->transform->TranslateTo( worldTrans.getOrigin().x(), worldTrans.getOrigin().y(), worldTrans.getOrigin().z() );
}
