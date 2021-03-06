#include "AssetController.h"

#include "AwesomiumView.h"
#include "Mesh.h"
#include "Texture.h"
#include "File.h"
#include "GraphosBehavior.h"

#define CONTENT_PATH "Resources/Assets/"

using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Utility;

void AssetController::Initialize( void )
{
	File::FileList files = File::ScanDir( CONTENT_PATH );

	string name;

	for( auto file = begin( files ); file != end( files ); ++file )
	{
		name = file->GetFileName().substr( 0, file->GetFileName().find( "." ) );

		if( file->GetDirectory() == CONTENT_PATH "Meshes/" )
		{
			ingredientShelf[ name ] = new Mesh( file->GetFullPath() );
		}
		else if( file->GetDirectory() == CONTENT_PATH "Textures/" )
		{
			ingredientShelf[ name ] = new Texture( file->GetFullPath() );
		}
	}
}

void AssetController::Shutdown( void )
{
	
	for( auto ingredient = begin( ingredientShelf ); ingredient != end( ingredientShelf ); ++ingredient )
	{
		//if( static_cast<AwesomiumView*>( ingredient->second ) || static_cast<Script*>( ingredient->second ) )
		{
			ingredient->second->Shutdown();
			delete ingredient->second;
		}
	}
	

	ingredientShelf.clear();
}

unordered_map<string, IComponent*> AssetController::ingredientShelf;
