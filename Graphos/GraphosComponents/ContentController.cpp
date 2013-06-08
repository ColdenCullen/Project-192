#include "ContentController.h"
#include "File.h"

#define CONTENT_PATH "Resources/Assets/"

using namespace std;
using namespace Graphos::Core;

bool ContentController::Initialize( void )
{
	File::FileList files = File::ScanDir( CONTENT_PATH );

	string name;

	for( int ii = 0; ii != files.size(); ++ii )
	{
		name = files[ ii ].name.substr( 0, files[ ii ].name.find( "." ) );

		if( files[ ii ].localPath == "Meshes/" )
		{
			components[ name ] = new Mesh( files[ ii ].GetFullPath() );
		}
		else if( files[ ii ].localPath == "Textures/" )
		{
			components[ name ] = new Texture( files[ ii ].GetFullPath() );
		}
	}

	return true;
}

void ContentController::Shutdown( void )
{
	for( auto ingredient = begin( components ); ingredient != end( components ); ++ingredient )
		delete ingredient->second;
		
	components.clear();
}