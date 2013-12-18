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
	// Save current scale
	//Math::Vector3 tempScale = *owner->transform->Scale();

	// Revert to unit scale
	//owner->transform->Scale( 1.0f/tempScale.x, 1.0f/tempScale.y, 1.0f/tempScale.z );

	// Send matrix
	//worldTrans.setFromOpenGLMatrix( owner->transform->WorldMatrix().dataArray );
	worldTrans.setRotation( *owner->transform->Rotation() );
	Math::Vector3 pos = *owner->transform->Position();
	worldTrans.setOrigin( btVector3( pos.x, pos.y, pos.z ) );

	// Revert from unit scale back to saved scale
	//owner->transform->Scale( tempScale.x, tempScale.y, tempScale.z );
}

void Graphos::Physics::GraphosMotionState::setWorldTransform( const btTransform& worldTrans )
{
	// Save current scale
	//Math::Vector3 tempScale = *owner->transform->Scale();

	// Revert to unit scale
	//owner->transform->Scale( 1.0f/tempScale.x, 1.0f/tempScale.y, 1.0f/tempScale.z );

	// Get matrix from Bullet
	worldTrans.getOpenGLMatrix( owner->transform->WorldMatrix().dataArray );

	// Revert from unit scale back to saved scale
	//owner->transform->Scale( tempScale.x, tempScale.y, tempScale.z );

	// Save rotations
	*owner->transform->rotation = worldTrans.getRotation();
	//btQuaternion wT = worldTrans.getRotation();
	//owner->transform->rotation->x = worldTrans.getRotation().x();
	//owner->transform->rotation->y = worldTrans.getRotation().y();
	//owner->transform->rotation->z = worldTrans.getRotation().z();

	// Save positions
	// TODO: Make access times not suck
	owner->transform->position->x = worldTrans.getOrigin().x();
	owner->transform->position->y = worldTrans.getOrigin().y();
	owner->transform->position->z = worldTrans.getOrigin().z();


}
