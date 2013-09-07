#include "StdAfx.h"
#include "ShaderController.h"

#include "WindowController.h"
#include "File.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#if defined( _WIN32 )
#include <windirent.h>
#elif defined( __APPLE__ )
#include <dirent.h>
#endif

using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Graphics;

#pragma region Helper Methods
#ifdef _WIN32

#include <Windows.h>

void OutputShaderErrorMessage( HWND hwnd, unsigned int shaderId, const char* shaderFilename )
{
	int logSize, i;
	char* infoLog;
	ofstream fout;
	wchar_t newString[128];
	unsigned int error, convertedChars;

	// Get the size of the string containing the information log for the failed shader compilation message.
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logSize);

	// Increment the size by one to handle also the null terminator.
	logSize++;

	// Create a char buffer to hold the info log.
	infoLog = new char[logSize];
	if( !infoLog )
		return;

	// Now retrieve the info log.
	glGetShaderInfoLog(shaderId, logSize, NULL, infoLog);

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.
	for(i=0; i<logSize; i++ )
		fout << infoLog[i];

	// Close the file.
	fout.close();

	// Convert the shader filename to a wide character string.
	error = mbstowcs_s( &convertedChars, newString, 128, shaderFilename, 128 );
	if( error != 0 )
		return;

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	//TODO: Fix error from here
	//MessageBox( hwnd, L"Error compiling shader.  Check shader-error.txt for message.", newString, MB_OK );

	delete[] infoLog;

	return;
}
#endif
#pragma endregion

void ShaderController::Initialize( void )
{
	char abspath[ 256 ];
#ifdef _WIN32
	_fullpath( abspath, ShaderPath.c_str(), MAX_PATH );
#else
	realpath( ShaderPath.c_str(), abspath );
#endif

#ifdef _WIN32
	DIR* dir;
	dirent* ent;
	// Open directory
	if( ( dir = opendir( abspath ) ) != NULL )
	{
		// Iterate through contents
		while( ( ent = readdir( dir ) ) != NULL )
		{
			if( ent->d_namlen > 5 && ent->d_name[ ent->d_namlen - 5 ] == 'f' )
			{
				string name = string( ent->d_name ).substr( 0, ent->d_namlen - 6 );

				AddShader( abspath, name );
			}
		}

		// Close dir
		closedir( dir );
	}
	else
	{
		throw exception( "Error reading shader dir." );
	}
#else
	throw exception( "Unsupported platform" );
#endif
}

GlShader& ShaderController::GetShader( string shaderName )
{
	return shaders.at( shaderName );
}

void ShaderController::AddShader( string path, string name )	
{
	// Load shader text
	string vertexShaderBuffer = File::ReadFile( path + name + ".vs.gl" );
	string fragmentShaderBuffer = File::ReadFile( path + name + ".fs.gl" );

	// If text is valid
	if( !vertexShaderBuffer.empty() && !fragmentShaderBuffer.empty() )
	{
		// Add shader to map
		shaders[ name ] = GlShader().Initialize( vertexShaderBuffer, fragmentShaderBuffer );
	}
	else
	{
		throw exception( "Error reading files." );
	}
}