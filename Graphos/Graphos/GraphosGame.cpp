/*
#include "GraphosGame.h"

#define _USE_READ_FILE
#define _USE_SCAN_DIR
#include "Helpers.h"

#include <vector>
#include <string>
#include <json/json.h>

#include "ScriptController.h"
#include "RigidBody.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "Physics.h"
#include "GraphicsController.h"
#include "AssetController.h"
#include "ShaderController.h"
#include "AwesomiumView.h"
#include "Input.h"
#include "Texture.h"
#include "Mesh.h"
#include "Time.h"

#define OBJECTS_PATH "Resources/Assets/Objects/"

using namespace Graphos::Core;
using namespace Graphos::Content;

void GraphosGame::Run( void )
{
	//////////////////////////////////////////////////////////////////////////
	// Initialize
	//////////////////////////////////////////////////////////////////////////

	// Initialize values and controllers
	bool isDone = Start();

	// Init time
	Time::Get().Update();

	// Loop until there is a quit message from the window or the user.
	while( !isDone )
	{
		if( CurrentState == GameState::Reseting )
			Reset();

		// Platform specific program stuff
		GraphicsController::Get().MessageLoop();

		//////////////////////////////////////////////////////////////////////////
		// Update
		//////////////////////////////////////////////////////////////////////////
		
		// Update time
		Time::Get().Update();

		// Update input
		Input::Get().Update();

		// Do the updating of the child class.
		isDone = !Update();

		// Update physics
		Physics::Get().Update();

		// Update the UI
		if( CurrentState == GameState::Menu )
			ui->Update( Time::Get().DeltaTime() );

		// Update objects in list
		if( CurrentState == GameState::Game )
		{
			if( !objectsLoaded )
				LoadObjects();

			// Update camera
			if( camera )
				camera->Update( Time::Get().DeltaTime() );

			for( auto iterator = objects->begin(); iterator != objects->end(); ++iterator )
				iterator->second.Update( Time::Get().DeltaTime() );	
		}

		//////////////////////////////////////////////////////////////////////////
		// Draw
		//////////////////////////////////////////////////////////////////////////

		// Begin drawing
		GraphicsController::Get().CallGLFunction( GraphicsController::BEGIN );

		// Draw objects in list
		if( CurrentState == GameState::Game )
		{
			// Update camera position
			if( camera )
				camera->Draw();

			for( auto iterator = objects->begin(); iterator != objects->end(); ++iterator )
				iterator->second.Draw();
		}

		// Draw in child class
		Draw();

		// Draw the UI last
		if( CurrentState == GameState::Menu )
			ui->Draw();

		// End drawing
		GraphicsController::Get().CallGLFunction( GraphicsController::END );
	}

	Stop();
}

void GraphosGame::DeleteObjects( void )
{
	if( objects != nullptr )
	{
		for( auto object = objects->begin(); object != objects->end(); ++object )
			object->second.Shutdown();

		GameObject::ClearObjects();
		objects = nullptr;

		objectsLoaded = false;
	}
}

void GraphosGame::Reset( void )
{
	Config::Get().LoadSettings();
	GraphicsController::Get().Reload();

	// Delete loaded objects
	DeleteObjects();

	// Call child shutdown
	Shutdown();

	// Shutdown UI and controllers
	delete ui;
	Physics::Get().Shutdown();
	AssetController::Get().Shutdown();
	ScriptController::Get().Shutdown();

	// Restart
	ScriptController::Get().Initialize();
	AssetController::Get().Initialize();
	Physics::Get().Initialize();
	ui = new UserInterface( this );
	Input::Get().ui = ui;

	CurrentState = GameState::Menu;

	Initialize();
}

bool GraphosGame::Start( void )
{
	objectsLoaded = false;
	CurrentState = GameState::Menu;
	objects = nullptr;
	camera = nullptr;

	bool isDone = false;

	if( !isDone && !Config::Get().LoadSettings() )
		isDone = true;

	if( !isDone && !GraphicsController::Get().Initialize() )
		isDone = true;

	if( !isDone && !AssetController::Get().Initialize() )
		isDone = true;

	if( !isDone && !Physics::Get().Initialize() )
		isDone = true;

	if( !isDone );
		ui = new UserInterface( this );

	Input::Get().ui = ui;

	if( !isDone && !Initialize() )
		isDone = true;

	return isDone;
}

void GraphosGame::Stop( void )
{
	// Delete loaded objects
	DeleteObjects();

	// Call child shutdown
	Shutdown();

	// Shutdown UI and controllers
	delete ui;
	Physics::Get().Shutdown();
	AssetController::Get().Shutdown();
	ScriptController::Get().Shutdown();
}

void GraphosGame::LoadObjects( void )
{
	unordered_map<string, string> files = Helpers::ScanDir( OBJECTS_PATH );
	Json::Reader reader;
	Json::Value root;

	Json::Value current;

	// For iterating (sometimes)
	int ii = 0;

	// Map for parents, to be added after all objects are loaded
	unordered_map<unsigned int, string> parentMap;

	for( auto file = begin( files ); file != end( files ); ++file )
	{
		if( reader.parse( Helpers::ReadFile( string( OBJECTS_PATH ).append( file->second ).append( file->first ) ), root ) )
		{
			if( ( current = root.get( "Name", root ) ) != root )
			{
				// Create object, get pointer to it
				string name = current.asString();
				unsigned int id = GameObject::CreateObject( name, &( ShaderController::Get().GetShader( root[ "Shader" ].asString() ) ) );
				GameObject* newObj = GameObject::GetGameObject( name );

				// Get parent
				if( ( current = root.get( "Parent", root ) ) != root )
				{
					parentMap[ id ] = current.asString();
				}

				// Set texture
				if( ( current = root.get( "Texture", root ) ) != root )
				{
					newObj->AddIngredient(
						AssetController::Get().GetContent<Texture>( current[ "Name" ].asString() )
					);
				}

				if( ( current = root.get( "Camera", root ) ) != root )
				{
					camera = new Camera( newObj );
					//newObj->AddIngredient( camera );
				}

				// Set physics Rigid Body object
				if( ( current = root.get( "Rigidbody", root ) ) != root )
				{
					Rigidbody* rb = new Rigidbody( newObj );

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
					rb->linearDrag = root.get( "Rigidbody", root ).get( "LinearDrag", root ).asDouble();
					rb->angularDrag = root.get( "Rigidbody", root ).get( "AngularDrag", root ).asDouble();

					if( ( currentRigidbody = current.get( "Constraints", root ) ) != root )
					{
						if( currentRigidbody.get( "Position", root ) != root )
						{
							rb->positionConstraints.x = static_cast<float>( currentRigidbody[ "Position" ][ "x" ].asBool() );
							rb->positionConstraints.y = static_cast<float>( currentRigidbody[ "Position" ][ "y" ].asBool() );
							rb->positionConstraints.z = static_cast<float>( currentRigidbody[ "Position" ][ "z" ].asBool() );
						}
						if( currentRigidbody.get( "Rotation", root ) != root )
						{
							rb->rotationConstraints.x = static_cast<float>( currentRigidbody[ "Rotation" ][ "x" ].asBool() );
							rb->rotationConstraints.y = static_cast<float>( currentRigidbody[ "Rotation" ][ "y" ].asBool() );
							rb->rotationConstraints.z = static_cast<float>( currentRigidbody[ "Rotation" ][ "z" ].asBool() );
						}
					}

					newObj->AddIngredient( rb );
				}

				// Add webview
				if( ( current = root.get( "AwesomiumView", root ) ) != root && ii == 0 )
					newObj->AddIngredient(
						new AwesomiumView(
							current[ "url" ].asString(),
							current[ "width" ].asUInt(),
							current[ "height" ].asUInt()
						)
					);

				// Add a script
				if( ( current = root.get( "Script", root ) ) != root )
					newObj->AddIngredient(
						ScriptController::Get().CreateObjectInstance(
							current[ "Class" ].asString(),
							id,
							newObj
						)
					);

				// Add a mesh
				if( ( current = root.get( "Mesh", root ) ) != root )
					newObj->AddIngredient(
						AssetController::Get().GetContent<Mesh>( current[ "Name" ].asString() )
					);

				// Transform object
				if( ( current = root.get( "Transform", root ) ) != root )
				{
					Json::Value currentTransform;

					if( ( currentTransform = current.get( "Scale", root ) ) != root )
						newObj->transform.Scale(
							currentTransform[ "x" ].asDouble(),
							currentTransform[ "y" ].asDouble(),
							currentTransform[ "z" ].asDouble()
						);
					if( ( currentTransform = current.get( "Position", root ) ) != root )
						newObj->transform.Translate(
							currentTransform[ "x" ].asDouble(),
							currentTransform[ "y" ].asDouble(),
							currentTransform[ "z" ].asDouble()
						);
					if( ( currentTransform = current.get( "Rotation", root ) ) != root )
						newObj->transform.Rotate(
							currentTransform[ "x" ].asDouble(),
							currentTransform[ "y" ].asDouble(),
							currentTransform[ "z" ].asDouble()
						);
				}

				// Setup collider
				if( ( current = root.get( "Collider", root ) ) != root )
				{
					Json::Value currentCol;
					string type = current[ "Type" ].asString();
					Collider* col;

					if( type == "Sphere" )
					{
						col = new SphereCollider( newObj );
						static_cast<SphereCollider*>( col )->radius = static_cast<float>( current[ "Radius" ].asDouble() );
					}
					else if( type == "Box" )
					{
						col = new BoxCollider( newObj );

						if( ( currentCol = current.get( "Size", root ) ) != root )
							static_cast<BoxCollider*>( col )->size = Vector3(
								currentCol[ "x" ].asDouble(),
								currentCol[ "y" ].asDouble(),
								currentCol[ "z" ].asDouble()
							);
						else
							static_cast<BoxCollider*>( col )->size = Vector3( 1.0f, 1.0f, 1.0f );
					}

					if( ( currentCol = current.get( "Offset", root ) ) != root )
					{
						col->centerOffset = Vector3(
							currentCol[ "x" ].asDouble(),
							currentCol[ "y" ].asDouble(),
							currentCol[ "z" ].asDouble()
						);
					}

					if( ( currentCol = current.get( "Bounce", root ) ) != root )
					{
						col->bounce = currentCol.asDouble();
					}

					newObj->AddIngredient<Collider>( col );
					Physics::Get().AddCollider( col );
				}
			}
		}
	}

	objects = &GameObject::GetObjectsList();

	for( auto parentPair = begin( parentMap ); parentPair != end( parentMap ); ++parentPair )
		GameObject::GetGameObject( parentPair->first )->transform.parent = &GameObject::GetGameObject( parentPair->second )->transform;

	objectsLoaded = true;
}
*/