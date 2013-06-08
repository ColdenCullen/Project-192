#include "AssetController.h"
#include "Mesh.h"
#include "Texture.h"

#define _USE_READ_FILE
#define _USE_SCAN_DIR
#include <Helpers.h>
#include "AwesomiumView.h"
#include "Script.h"

#define CONTENT_PATH "Resources/Assets/"

using namespace Graphos::Content;

bool AssetController::Initialize( void )
{
	unordered_map<string, string> files = Helpers::ScanDir( CONTENT_PATH );

	string name;

	for( auto pair = begin( files ); pair != end( files ); ++pair )
	{
		name = pair->first.substr( 0, pair->first.find( "." ) );

		if( pair->second == "Meshes/" )
		{
			ingredientShelf[ name ] = new Mesh( string( CONTENT_PATH ).append( pair->second ).append( pair->first ) );
		}
		else if( pair->second == "Textures/" )
		{
			ingredientShelf[ name ] = new Texture( string( CONTENT_PATH ).append( pair->second ).append( pair->first ) );
		}
	}

	return true;
}

void AssetController::Shutdown( void )
{
	/*
	for( auto ingredient = begin( ingredientShelf ); ingredient != end( ingredientShelf ); ++ingredient )
	{
		if( static_cast<AwesomiumView*>( ingredient->second ) || static_cast<Script*>( ingredient->second ) )
		{
			ingredient->second->Shutdown();
			delete ingredient->second;
		}
	}
	*/

	ingredientShelf.clear();
}