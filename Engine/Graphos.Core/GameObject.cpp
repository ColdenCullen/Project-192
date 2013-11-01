#include "GameObject.h"
#include "AwesomiumView.h"
#include "Script.h"
#include "AssetController.h"
#include "Camera.h"
#include "RigidBody.h"
#include "Mesh.h"
#include "ScriptController.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "Texture.h"
#include "GraphosGame.h"

using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Physics;
using namespace Graphos::Graphics;

GameObject* GameObject::CreateFromJson( Json::Value object )
{
	Json::Value current;
	GameObject* obj = new GameObject( ShaderController::GetShader( object[ "Shader" ].asString() ) );

	// Get parent
	if( ( current = object.get( "Parent", object ) ) != object )
	{
		//parentMap[ id ] = current.asString();
	}

	// Set texture
	if( ( current = object.get( "Texture", object ) ) != object )
	{
		obj->AddComponent(
			AssetController::GetContent<Texture>( current[ "Name" ].asString() )
		);
	}

	if( ( current = object.get( "Camera", object ) ) != object )
	{
		auto cam = new Camera( obj );
		obj->AddComponent( cam );
		GraphosGame::camera = cam;
	}

	// Set physics Rigid Body object
	if( ( current = object.get( "Rigidbody", object ) ) != object )
	{
		RigidBody* rb = new RigidBody( obj );

		// Get rigid body's values
		Json::Value currentRigidbody = current[ "LinearVelocity" ];

		// Add initial velocities and drags
		rb->linearVelocity.x = currentRigidbody[ "x" ].asDouble();
		rb->linearVelocity.y = currentRigidbody[ "y" ].asDouble();
		rb->linearVelocity.z = currentRigidbody[ "z" ].asDouble();

		currentRigidbody = current[ "AngularVelocity" ];

		// Add initial velocities and drags
		rb->angularVelocity.x = currentRigidbody[ "x" ].asDouble();
		rb->angularVelocity.y = currentRigidbody[ "y" ].asDouble();
		rb->angularVelocity.z = currentRigidbody[ "z" ].asDouble();

		// Add initial velocities and drags
		rb->linearDrag = current.get( "LinearDrag", object ).asDouble();
		rb->angularDrag = current.get( "AngularDrag", object ).asDouble();

		if( ( currentRigidbody = current.get( "Constraints", object ) ) != object )
		{
			if( currentRigidbody.get( "Position", object ) != object )
			{
				rb->positionConstraints.x = static_cast<float>( currentRigidbody[ "Position" ][ "x" ].asBool() );
				rb->positionConstraints.y = static_cast<float>( currentRigidbody[ "Position" ][ "y" ].asBool() );
				rb->positionConstraints.z = static_cast<float>( currentRigidbody[ "Position" ][ "z" ].asBool() );
			}
			if( currentRigidbody.get( "Rotation", object ) != object )
			{
				rb->rotationConstraints.x = static_cast<float>( currentRigidbody[ "Rotation" ][ "x" ].asBool() );
				rb->rotationConstraints.y = static_cast<float>( currentRigidbody[ "Rotation" ][ "y" ].asBool() );
				rb->rotationConstraints.z = static_cast<float>( currentRigidbody[ "Rotation" ][ "z" ].asBool() );
			}
		}

		obj->AddComponent( rb );
	}

	// Add webview
	if( ( current = object.get( "AwesomiumView", object ) ) != object )
		obj->AddComponent(
			new AwesomiumView(
				current[ "url" ].asString(),
				current[ "width" ].asUInt(),
				current[ "height" ].asUInt()
			)
		);

	// Add a mesh
	if( ( current = object.get( "Mesh", object ) ) != object )
	{
		obj->AddComponent(
			AssetController::GetContent<Mesh>( current[ "Name" ].asString() )
		);
	}

	// Transform object
	if( ( current = object.get( "Transform", object ) ) != object )
	{
		Json::Value currentTransform;

		if( ( currentTransform = current.get( "Scale", object ) ) != object )
			obj->transform->Scale(
				currentTransform[ "x" ].asDouble(),
				currentTransform[ "y" ].asDouble(),
				currentTransform[ "z" ].asDouble()
			);
		if( ( currentTransform = current.get( "Position", object ) ) != object )
			obj->transform->Translate(
				currentTransform[ "x" ].asDouble(),
				currentTransform[ "y" ].asDouble(),
				currentTransform[ "z" ].asDouble()
			);
		if( ( currentTransform = current.get( "Rotation", object ) ) != object )
			obj->transform->Rotate(
				currentTransform[ "x" ].asDouble(),
				currentTransform[ "y" ].asDouble(),
				currentTransform[ "z" ].asDouble()
			);
	}

	// Add script
	if( ( current = object.get( "Script", object ) ) != object )
	{
		obj->AddComponent(
			ScriptController::Get().CreateObjectInstance( current[ "Class" ].asString(), obj )
		);
	}

	// Setup collider
	if( ( current = object.get( "Collider", object ) ) != object )
	{
		Json::Value currentCol;
		string type = current[ "Type" ].asString();
		Collider* col;

		if( type == "Sphere" )
		{
			col = new SphereCollider( obj );
			static_cast<SphereCollider*>( col )->radius = static_cast<float>( current[ "Radius" ].asDouble() );
		}
		else// if( type == "Box" )
		{
			col = new BoxCollider( obj );

			if( ( currentCol = current.get( "Size", object ) ) != object )
				static_cast<BoxCollider*>( col )->size = Vector3(
				currentCol[ "x" ].asDouble(),
				currentCol[ "y" ].asDouble(),
				currentCol[ "z" ].asDouble()
				);
			else
				static_cast<BoxCollider*>( col )->size = Vector3( 1.0f, 1.0f, 1.0f );
		}

		if( ( currentCol = current.get( "Offset", object ) ) != object )
		{
			col->centerOffset = Vector3(
				currentCol[ "x" ].asDouble(),
				currentCol[ "y" ].asDouble(),
				currentCol[ "z" ].asDouble()
			);
		}

		if( ( currentCol = current.get( "Bounce", object ) ) != object )
		{
			col->bounce = currentCol.asDouble();
		}

		obj->AddComponent<Collider>( col );
		Physics::Physics::AddCollider( col );
	}

	return obj;
}


void GameObject::Update( void )
{
	for( auto ingredient = begin( componentList ); ingredient != end( componentList ); ++ingredient )
		ingredient->second->Update();
}

void GameObject::Draw( void )
{
	//shader->Use();
	shader->SetModelMatrix( transform->WorldMatrix() );
	// TODO...what did/does this do?...
	// this SetUniform was removed...needs refactoring?
//	shader->SetUniform( "shaderTexture", 0 );

	for( auto ingredient = begin( componentList ); ingredient != end( componentList ); ++ingredient )
		ingredient->second->Draw( shader );
}

void GameObject::Shutdown( void )
{
	for( auto ingredient = begin( componentList ); ingredient != end( componentList ); ++ingredient )
	{
		if( dynamic_cast<AwesomiumView*>( ingredient->second ) || dynamic_cast<Script*>( ingredient->second ) )
		{
			ingredient->second->Shutdown();
			delete ingredient->second;
		}
	}

	componentList.clear();

	delete_s( transform );
}