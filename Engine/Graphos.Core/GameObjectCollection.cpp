#include "GameObjectCollection.h"

// For parsing and building objects
#include "File.h"
#include <json\json.h>

// Controllers used to add components
#include "OutputController.h"

using namespace std;
using namespace Graphos::Core;

void GameObjectCollection::LoadObjects( string assetPath )
{
	// Read in list of files
	File::FileList fileList = File::ScanDir( "Resources/Assets/Objects/" + assetPath );
	// Json reader
	Json::Reader reader;
	// Root of current file
	Json::Value root;

	// Function to add objects to the list
	auto addObj = [&]( Json::Value object )
	{
		auto name = object[ "Name" ].asString();

		if( nameMap.find( name ) != end( nameMap ) )
			OutputController::PrintMessage( OutputType::OT_ERROR, "Object name " + name + " already in use." );

		objectList[ currentId ] = GameObject::CreateFromJson( object );
		nameMap[ name ] = currentId++;
	};

	// Map for parents, to be added after all objects are loaded
	unordered_map<unsigned int, string> parentMap;

	for( int fileIndex = 0; fileIndex < fileList.size(); ++fileIndex )
	{
		if( reader.parse( fileList[ fileIndex ].GetContents(), root ) )
		{
			if( root.isArray() )
			{
				for( int ii = 0; ii < root.size(); ++ii )
					addObj( root[ ii ] );
			}
			else
			{
				addObj( root );
			}
		}
		else
		{
			OutputController::PrintMessage( OutputType::OT_ERROR, "Invalid object json in " + fileList[ fileIndex ].GetFileName() );
		}
	}

	for( auto parentPair = begin( parentMap ); parentPair != end( parentMap ); ++parentPair )
		GetObjectById( parentPair->first )->transform->parent = GetObjectByName( parentPair->second )->transform;
}

GameObject* GameObjectCollection::GetObjectById( unsigned int id )
{
	auto it = objectList.find( id );

	if( it != end( objectList ) )
		return it->second;
	else
		return nullptr;
}

GameObject*	GameObjectCollection::GetObjectByName( string name )
{
	auto it = nameMap.find( name );

	if( it != end( nameMap ) )
		return objectList.at( it->second );
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
		{
			object->second->Shutdown();
			delete object->second;
		}

	objectList.clear();
	nameMap.clear();
	currentId = 0;
}

void GameObjectCollection::CallFunction( void (GameObject::*func)( void ) )
{
	for( auto iterator = begin( objectList ); iterator != end( objectList ); ++iterator )
		(iterator->second->*func)();
}