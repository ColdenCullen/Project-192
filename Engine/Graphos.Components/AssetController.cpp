#include "AssetController.h"

#include "AwesomiumView.h"
#include "Mesh.h"
#include "Texture.h"
#include "File.h"
#include "Script.h"

#define CONTENT_PATH "Resources/Assets/"

using namespace std;
using namespace Graphos::Core;

void AssetController::Initialize( void )
{
	File::FileList files = File::ScanDir( CONTENT_PATH );

	string name;

	for( auto file = begin( files ); file != end( files ); ++file )
	{
		name = file->GetFileName().substr( 0, file->GetFileName().find( "." ) );

		if( file->GetLocalPath() == "Meshes/" )
		{
			ingredientShelf[ name ] = new Mesh( file->GetFullPath() );
		}
		else if( file->GetLocalPath() == "Textures/" )
		{
			ingredientShelf[ name ] = new Texture( file->GetFullPath() );
		}
	}
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