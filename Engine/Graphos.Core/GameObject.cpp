#include "GameObject.h"
#include "AwesomiumView.h"
#include "AssetController.h"
#include "Camera.h"
#include "Mesh.h"
#include "ScriptController.h"
#include "Texture.h"
#include "GraphosGame.h"
#include "GraphosMotionState.h"
#include "PhysicsController.h"

using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Physics;
using namespace Graphos::Graphics;

GameObject* GameObject::CreateFromJson( JsonObject object )
{
	JsonObject component;
	GameObject* obj = new GameObject( ShaderController::GetShader( object.Get<string>( "Shader" ) ) );

	// Get parent
	if( object.TryGet( "Parent", component ) )
	{
		//parentMap[ id ] = current.asString();
	}

	// Set texture
	if( object.TryGet( "Texture", component ) )
	{
		obj->AddComponent(
			AssetController::GetContent<Texture>( component.Get<string>( "Name" ) )
		);
	}

	if( object.TryGet( "Camera", component ) )
	{
		auto cam = new Camera( obj );
		obj->AddComponent( cam );
		GraphosGame::camera = cam;
	}	

	// Add webview
	if( object.TryGet( "AwesomiumView", component ) )
		obj->AddComponent(
			new AwesomiumView(
				component.Get<string>( "url" ),
				component.Get<gUInt>( "width" ),
				component.Get<gUInt>( "height" )
			)
		);

	// Add a mesh
	if( object.TryGet( "Mesh", component ) )
	{
		obj->AddComponent(
			AssetController::GetContent<Mesh>( component.Get<string>( "Name" ) )
		);
	}

	// Transform object
	if( object.TryGet( "Transform", component ) )
	{
		JsonObject currentTransform;

		if( component.TryGet( "Scale", currentTransform ) )
			obj->transform->Scale( currentTransform.Get<Vector3>( "" ) );
		if( component.TryGet( "Position", currentTransform ) )
			obj->transform->TranslateTo( currentTransform.Get<Vector3>( "" ) );
		if( component.TryGet( "Rotation", currentTransform ) )
			obj->transform->Rotate( currentTransform.Get<Vector3>( "" ) );
	}

	// Set physics Rigid Body object
	if(  object.TryGet( "Physics", component ) )
	{
		auto gms = new GraphosMotionState( obj );
		gFloat mass;
		gFloat restitution;
		gFloat friction;
		gFloat rollingFriction;

		mass = component.Get<gFloat>( "Mass" );
		// TODO: Make these optional

		restitution = component.Get<gFloat>( "Restitution" );
		friction = component.Get<gFloat>( "Friction" );
		rollingFriction = component.Get<gFloat>( "RollingFriction" );

		PhysicsController::CreatePhysicsObject( gms, mass, restitution, friction, rollingFriction );

		obj->AddComponent( gms );
	}

	// Add script
	if( object.TryGet( "Script", component ) )
	{
		auto script = ScriptController::Get().CreateObjectInstance( component.Get<string>( "Class" ), obj );

		if( component.TryGet( "Variables", component ) )
			script->SetInitialValues( component );

		obj->AddComponent( script );
	}

	return obj;
}


void GameObject::Update( void )
{
	for( auto component : componentList )
		component.second->Update();
}

void GameObject::Draw( void )
{
	shader->SetModelMatrix( transform->WorldMatrix() );

	for( auto component : componentList )
		component.second->Draw( shader );
}

void GameObject::Shutdown( void )
{
	for( auto ingredient = begin( componentList ); ingredient != end( componentList ); ++ingredient )
	{
		if( dynamic_cast<AwesomiumView*>( ingredient->second ) || dynamic_cast<GraphosBehavior*>( ingredient->second ) )
		{
			ingredient->second->Shutdown();
			delete ingredient->second;
		}
	}

	componentList.clear();

	delete_s( transform );
}