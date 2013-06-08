#include "AssetController.h"
#include "Mesh.h"
#include "Texture.h"
#include "File.h"
#include "AwesomiumView.h"
#include "Script.h"

#define CONTENT_PATH "Resources/Assets/"

using namespace std;
using namespace Graphos::Core;

bool AssetController::Initialize( void )
{
	File::FileList files = File::ScanDir( CONTENT_PATH );

	string name;

	for( auto file = begin( files ); file != end( files ); ++file )
	{
		name = file->name.substr( 0, file->name.find( "." ) );

		if( file->localPath == "Meshes/" )
		{
			ingredientShelf[ name ] = new Mesh( file->GetFullPath() );
		}
		else if( file->localPath == "Textures/" )
		{
			ingredientShelf[ name ] = new Texture( file->GetFullPath() );
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