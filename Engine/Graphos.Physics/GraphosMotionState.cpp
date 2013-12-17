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
	worldTrans.setFromOpenGLMatrix( owner->transform->WorldMatrix().dataArray );
}

void Graphos::Physics::GraphosMotionState::setWorldTransform( const btTransform& worldTrans )
{
	// TODO: FIX FOR RUNTIME SCALING
	worldTrans.getOpenGLMatrix( owner->transform->WorldMatrix().dataArray );

	// Save rotations
	// TODO: Make access times not suck
	owner->transform->rotation->x = worldTrans.getRotation().x();
	owner->transform->rotation->y = worldTrans.getRotation().y();
	owner->transform->rotation->z = worldTrans.getRotation().z();

	// Save positions
	// TODO: Make access times not suck
	owner->transform->position->x = worldTrans.getOrigin().x();
	owner->transform->position->y = worldTrans.getOrigin().y();
	owner->transform->position->z = worldTrans.getOrigin().z();
}
