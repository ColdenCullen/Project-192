#include "StdAfx.h"
#include "ShaderController.h"

#include "WindowController.h"
#include "File.h"

#include "GlShader.h"
#include "DXShader.h"

#if defined( _WIN32 )
#include <windirent.h>
#elif defined( __APPLE__ )
#include <dirent.h>
#endif
#include "GraphicsController.h"

#define SHADER_PATH string("Resources\\Shaders\\")

using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Graphics;

void ShaderController::Initialize( void )
{
#if 0
	char cAbsPath[ 256 ];
#ifdef _WIN32
	_fullpath( cAbsPath, SHADER_PATH.c_str(), MAX_PATH );
#else
	realpath( SHADER_PATH.c_str(), abspath );
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
			if( ent->d_namlen < 8 )
				continue;

			string fileName = ent->d_name;

			// Check shader type
			if( fileName.substr( ent->d_namlen - 8 ) == ".fs.glsl" &&
				GraphicsController::GetActiveAdapter() == GraphicsAdapter::OpenGL )
			{
				string name = fileName.substr( 0, ent->d_namlen - 8 );

				shaders[ name ] = new GlShader( absPath + name + ".vs.glsl", absPath + name + ".fs.glsl" );
			}
			else if( fileName.substr( ent->d_namlen - 8 ) == ".fs.hlsl" &&
				GraphicsController::GetActiveAdapter() == GraphicsAdapter::DirectX )
			{
				string name = fileName.substr( 0, ent->d_namlen - 8 );

				shaders[ name ] = new DXShader( absPath + name + ".vs.hlsl", absPath + name + ".fs.hlsl" );
			}
		}

		// Close dir
		closedir( dir );
	}
	else
	{
		throw exception( "Error reading shader dir." );
	}
#endif
}

IShader* ShaderController::GetShader( string shaderName )
{
	return shaders.at( shaderName );
}

void ShaderController::Shutdown( void )
{
	for( auto shader : shaders )
	{
		shader.second->Shutdown();
		delete shader.second;
	}
	shaders.clear();
}

unordered_map<string, IShader*> ShaderController::shaders;
