#include "GameObjectCollection.h"

// For parsing and building objects
#include "File.h"
#include "JsonController.h"

// Controllers used to add components
#include "OutputController.h"
#include "ScriptController.h"
#include "TaskManager.h"

using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Utility;

void GameObjectCollection::LoadObjects( string assetPath /* = "" */ )
{
	// Function to add objects to the list
	auto addObj = [&]( JsonObject object )
	{
		auto name = object.Get<string>( "Name" );

		if( nameMap.find( name ) != end( nameMap ) )
			OutputController::PrintMessage( OutputType::Error, "Object name " + name + " already in use." );

		objectList[ currentId ] = GameObject::CreateFromJson( object );
		nameMap[ name ] = currentId++;
	};

	for( auto object : JsonController::Get( "Objects" + ( assetPath.size() ? "." + assetPath : "" ) ).node )
	{
		if( object.isArray() )
		{
			for( gInt ii = 0; ii < object.size(); ++ii )
				addObj( object[ ii ] );
		}
		else
		{
			addObj( object );
		}
	}

	ScriptController::Get().InitializeObjects( this );
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
	{
		for( auto object = begin( objectList ); object != end( objectList ); ++object )
		{
			object->second->Shutdown();
			delete object->second;
		}
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