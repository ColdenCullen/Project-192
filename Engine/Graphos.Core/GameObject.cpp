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
#include "AmbientLight.h"

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

	// Add physics to the object
	if( object.TryGet( "Physics", component ) )
	{

		// Build a motion state for discussion between physics and graphics
		auto gms = new GraphosMotionState( obj );

		// physConfig holds options read in from JSON
		PhysicsController::PhysicsConfig physConfig;


		// Mass is a required setting for physics objects
		physConfig.mass = component.Get<gFloat>( "Mass" );

		//
		// Look for optional settings
		//
		gFloat physicsSetting;

		// Friction
		if( component.TryGet( "Friction", physicsSetting ) )
			physConfig.friction = physicsSetting;
		// Rolling Friction
		if( component.TryGet( "RollingFriction", physicsSetting ) )
			physConfig.rollingFriction = physicsSetting;
		// Restitution
		if( component.TryGet( "Restitution", physicsSetting ) )
			physConfig.restitution = physicsSetting;

		// Initial Inertia
		JsonObject inertiaObject;
		if( component.TryGet( "InitialInertia", inertiaObject ) )
		{
			
			inertiaObject.TryGet( "x", physConfig.initialInertia.x );
			inertiaObject.TryGet( "y", physConfig.initialInertia.y );
			inertiaObject.TryGet( "z", physConfig.initialInertia.z );
			
		}

		// Collision Shape
		physConfig.collisionDimensions.x = 1.0f;
		physConfig.collisionDimensions.y = 1.0f;
		physConfig.collisionDimensions.z = 1.0f;
		JsonObject bodyDimenObject;
		if( component.TryGet( "BodyDimensions", bodyDimenObject ) )
		{

			bodyDimenObject.TryGet( "x", physConfig.collisionDimensions.x );
			bodyDimenObject.TryGet( "y", physConfig.collisionDimensions.y );
			bodyDimenObject.TryGet( "z", physConfig.collisionDimensions.z );
		}
		
		//physConfig.collisionShape = PhysicsController::G_SPHERE;

		// Create our new object and add it to the simulation
		Physics::PhysicsController::CreatePhysicsObject( gms, &physConfig );

		// Link the physics sim to our graphics object
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
	shader->SetUniformMatrix( "rotationMatrix", transform->RotationMatrix() );

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
