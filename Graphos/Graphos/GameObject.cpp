#include "GameObject.h"
#include "AwesomiumView.h"
#include "Script.h"

using namespace std;
using namespace Graphos::Core;

GameObject* GameObject::GetGameObject( string name )
{
	auto it = nameMap.find( name );

	if( it != end( nameMap ) )
		return &objectList[ it->second ];
	else
		return nullptr;
}

GameObject* GameObject::GetGameObject( unsigned int id )
{
	auto object = objectList.find( id );

	if( object != end( objectList ) )
		return &object->second;
	else
		return nullptr;
}

unsigned int GameObject::CreateObject( string name, Shader* shader )
{
	if( nameMap.find( name ) == end( nameMap ) )
	{
		objectList[ currentId ] = GameObject( shader );
		nameMap[ name ] = currentId;

		return currentId++;
	}
	else
	{
		return -1;
	}
}

unsigned int GameObject::CreateObject( string name, GameObject newObj )
{
	if( nameMap.find( name ) == end( nameMap ) )
	{
		objectList[ currentId ] = newObj;
		nameMap[ name ] = currentId;

		return currentId++;
	}
	else
	{
		return -1;
	}
}

bool GameObject::Update( float deltaTime )
{
	bool result = true;

	for( auto ingredient = begin( componentList ); ingredient != end( componentList ); ++ingredient )
		if( !ingredient->second->Update() )
			result = false;

	return result;
}

void GameObject::Draw( void )
{
	shader->Use();
	shader->SetUniform( "modelMatrix", transform.WorldMatrix() );
	shader->SetUniform( "shaderTexture", 0 );

	for( auto ingredient = begin( componentList ); ingredient != end( componentList ); ++ingredient )
		ingredient->second->Draw();
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

	objectList.clear();
}

// Initializes map
unordered_map<unsigned int, GameObject> GameObject::objectList;
unordered_map<string, unsigned int>		GameObject::nameMap;

unsigned int GameObject::currentId = 0;