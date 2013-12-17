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

	/*
	btVector3* tempVec3 = new btVector3(	owner->transform->Position()->x,
		owner->transform->Position()->y,
		owner->transform->Position()->z);
	worldTrans.setOrigin( *tempVec3 );
	*/
	worldTrans.setFromOpenGLMatrix( owner->transform->WorldMatrix().dataArray );


}

void Graphos::Physics::GraphosMotionState::setWorldTransform( const btTransform& worldTrans )
{
	/*
	// Update position of object
	btVector3 tempOrigin = worldTrans.getOrigin();
	owner->transform->TranslateTo( tempOrigin.x(), tempOrigin.y(), tempOrigin.z() );
	*/
	// TODO: Update position/rotation/scale
	// TODO: FIX FOR RUNTIME SCALING
	worldTrans.getOpenGLMatrix( owner->transform->WorldMatrix().dataArray );
	//worldTrans.

	// TODO: Rotation via Quaternions
}
