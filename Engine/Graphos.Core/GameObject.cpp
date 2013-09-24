#include "GameObject.h"
#include "AwesomiumView.h"
#include "Script.h"

using namespace std;
using namespace Graphos::Core;

void GameObject::Update( void )
{
	for( auto ingredient = begin( componentList ); ingredient != end( componentList ); ++ingredient )
		ingredient->second->Update();
}

void GameObject::Draw( void )
{
	//shader->Use();
	shader->SetModelMatrix( transform.WorldMatrix() );
	shader->SetUniform( "shaderTexture", 0 );

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
}

// Initializes map
//unordered_map<unsigned int, GameObject> GameObject::objectList;
//unordered_map<string, unsigned int>		GameObject::nameMap;
//
//unsigned int GameObject::currentId = 0;