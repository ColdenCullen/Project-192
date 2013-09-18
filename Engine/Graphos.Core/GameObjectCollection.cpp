#include "GameObjectCollection.h"

// For parsing and building objects
#include "File.h"
#include <json\json.h>

// Controllers used to add components
#include "AssetController.h"
#include "ScriptController.h"
#include "ShaderController.h"

// Basic components to be added
#include "AwesomiumView.h"
#include "BoxCollider.h"
#include "Camera.h"
#include "Mesh.h"
#include "RigidBody.h"
#include "SphereCollider.h"
#include "Texture.h"

using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Physics;
using namespace Graphos::Graphics;

#pragma region Load Objects
void GameObjectCollection::LoadObjects( string assetPath )
{
	File::FileList fileList = File::ScanDir( "Resources/Assets/Objects/" + assetPath );
	Json::Reader reader;
	Json::Value root;

	Json::Value current;

	// For iterating (sometimes)
	int ii = 0;

	// Map for parents, to be added after all objects are loaded
	unordered_map<unsigned int, string> parentMap;

	for( int fileIndex = 0; fileIndex < fileList.size(); ++fileIndex )
	{
		if( reader.parse( fileList[ fileIndex ].GetContents(), root ) )
		{
			if( ( current = root.get( "Name", root ) ) != root )
			{
				// Create object, get pointer to it
				string name = current.asString();
				unsigned int id = CreateObject( name, &( ISingleton<ShaderController>::Get().GetShader( root[ "Shader" ].asString() ) ) );
				GameObject* newObj = GetObjectById( id );

				// Get parent
				if( ( current = root.get( "Parent", root ) ) != root )
				{
					parentMap[ id ] = current.asString();
				}

				// Set texture
				if( ( current = root.get( "Texture", root ) ) != root )
				{
					newObj->AddComponent(
						ISingleton<AssetController>::Get().GetContent<Texture>( current[ "Name" ].asString() )
					);
				}

				if( ( current = root.get( "Camera", root ) ) != root )
				{
					auto camera = new Camera( newObj );
					newObj->AddComponent( camera );
				}

				// Set physics Rigid Body object
				if( ( current = root.get( "Rigidbody", root ) ) != root )
				{
					RigidBody* rb = new RigidBody( newObj );

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

					newObj->AddComponent( rb );
				}

				// Add webview
				if( ( current = root.get( "AwesomiumView", root ) ) != root && ii == 0 )
					newObj->AddComponent(
						new AwesomiumView(
							current[ "url" ].asString(),
							current[ "width" ].asUInt(),
							current[ "height" ].asUInt()
						)
					);

				// Add a script
				if( ( current = root.get( "Script", root ) ) != root )
					newObj->AddComponent(
						ISingleton<ScriptController>::Get().CreateObjectInstance(
							current[ "Class" ].asString(),
							id,
							newObj
						)
					);

				// Add a mesh
				if( ( current = root.get( "Mesh", root ) ) != root )
					newObj->AddComponent(
						ISingleton<AssetController>::Get().GetContent<Mesh>( current[ "Name" ].asString() )
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

					newObj->AddComponent<Collider>( col );
					ISingleton<Physics::Physics>::Get().AddCollider( col );
				}
			}
			else
			{
				throw exception( "Invalid object: no 'Name' property." );
			}
		}
		else
		{
			throw exception( "Invalid object: invalid JSON." );
		}
	}

	for( auto parentPair = begin( parentMap ); parentPair != end( parentMap ); ++parentPair )
		GetObjectById( parentPair->first )->transform.parent = &GetObjectByName( parentPair->second )->transform;
}
#pragma endregion

unsigned int GameObjectCollection::CreateObject( string name, Shader* shader )
{
	if( nameMap.find( name ) != end( nameMap ) )
		throw exception( "Name given has already been used" );

	objectList[ currentId ] = GameObject( shader );
	nameMap[ name ] = currentId;

	return currentId++;
}

GameObject* GameObjectCollection::GetObjectById( unsigned int id )
{
	auto it = objectList.find( id );

	if( it != end( objectList ) )
		return &it->second;
	else
		return nullptr;
}

GameObject*	GameObjectCollection::GetObjectByName( string name )
{
	auto it = nameMap.find( name );

	if( it != end( nameMap ) )
		return &objectList.at( it->second );
	else
		return nullptr;
}

void GameObjectCollection::RemoveObjectById( unsigned int id )
{
	auto it = objectList.find( id );

	if( it != end( objectList ) )
		objectList.erase( it );
}

void GameObjectCollection::RemoveObjectByName( string name )
{
	auto it = nameMap.find( name );

	if( it != end( nameMap ) )
		objectList.erase( it->second );
}

void GameObjectCollection::ClearObjects( void )
{
	if( objectList.size() > 0 )
		for( auto object = begin( objectList ); object != end( objectList ); ++object )
			object->second.Shutdown();

	objectList.clear();
	nameMap.clear();
	currentId = 0;
}

void GameObjectCollection::CallFunction( void (GameObject::*func)( void ) )
{
	for( auto iterator = begin( objectList ); iterator != end( objectList ); ++iterator )
		(iterator->second.*func)();
}