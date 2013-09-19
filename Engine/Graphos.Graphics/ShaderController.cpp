#include "StdAfx.h"
#include "ShaderController.h"

#include "WindowController.h"
#include "File.h"

#include "GlShader.h"
#include "CgShader.h"

#if defined( _WIN32 )
#include <windirent.h>
#elif defined( __APPLE__ )
#include <dirent.h>
#endif

using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Graphics;

void ShaderController::Initialize( void )
{
	char cAbsPath[ 256 ];
#ifdef _WIN32
	_fullpath( cAbsPath, ShaderPath.c_str(), MAX_PATH );
#else
	realpath( ShaderPath.c_str(), abspath );
#endif
	string absPath = cAbsPath;

	DIR* dir;
	dirent* ent;

	// Open directory
	if( ( dir = opendir( cAbsPath ) ) != NULL )
	{
		// Iterate through contents
		while( ( ent = readdir( dir ) ) != NULL )
		{
			// If the selected file name is less than 3 characters long, skip it.
			if( ent->d_namlen < 3 )
				continue;

			string fileName = ent->d_name;

			// Check shader type
			if( fileName.substr( ent->d_namlen - 6 ) == ".fs.gl" )
			{
				string name = fileName.substr( 0, ent->d_namlen - 6 );

				shaders[ name ] = &( new GlShader() )->Initialize( absPath + name + ".vs.gl", absPath + name + ".fs.gl" );
			}
			else if( fileName.substr( ent->d_namlen - 6 ) == ".fs.cg" )
			{
				string name = fileName.substr( 0, ent->d_namlen - 6 );
				
				shaders[ name ] = new CgShader( absPath + name + ".vs.cg", absPath + name + ".fs.cg" );
			}
			else if( fileName.substr( ent->d_namlen - 5 ) == ".cgfx" )
			{
				string name = fileName.substr( 0, ent->d_namlen - 5 );

				shaders[ name ] = new CgShader( absPath + fileName );
			}
		}

		// Close dir
		closedir( dir );
	}
	else
	{
		throw exception( "Error reading shader dir." );
	}
}

Shader& ShaderController::GetShader( string shaderName )
{
	return *shaders.at( shaderName );
}

void ShaderController::Shutdown( void )
{
	for( auto shader : shaders )
	{
		delete shader.second;
	}
	shaders.clear();
}