#include "File.h"

// Include dirent
#if defined( _WIN32 )
 #include <windirent.h>
#elif defined( __APPLE__ )
 #include <dirent.h>
#endif

// For DFSing
#include <stack>

// Include stdlib files for reading files
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace Graphos::Utility;

#pragma region Static
string File::ReadFile( string filePath )
{
	ifstream fileStream( filePath.c_str() );

	if( !fileStream.is_open() )
		throw exception( "File/path is broken." );

	stringstream shaderData;
	shaderData << fileStream.rdbuf();
	fileStream.close();

	return shaderData.str();
}

File::FileList File::ScanDir( string dirPath )
{
	FileList files;
	stack<string> directories;
	stack<string> localDirs;
	string current;
	string currentLocal;

	directories.push( dirPath );
	localDirs.push( "" );

	DIR* dir;
	dirent* ent;

	// Loop through directories
	while( directories.size() )
	{
		current = directories.top();
		currentLocal = localDirs.top();
		directories.pop();
		localDirs.pop();

		// Open directory and check for validity
		if( ( dir = opendir( string( current ).c_str() ) ) == NULL )
			throw exception( "Directory specified is broken." );

		// Iterate through contents
		while( ( ent = readdir( dir ) ) != NULL )
		{	// If the name is longer than two (to filter out '.' and '..')
			if( ent->d_namlen > 2 )
			{	// If the dirent is a directory, push it on to the stack, else put it in the list
				if( ent->d_type == DT_DIR )
				{
					directories.push( current + ent->d_name + "/" );
					localDirs.push( currentLocal + ent->d_name + "/" );
				}
				else if( ent->d_type == DT_REG )
				{
					files.push_back( File( current + ent->d_name) );
				}
			}	
		}

		// Close dir
		closedir( dir );
	}

	return files;
}
#pragma endregion

File::File( string filePath )
{
	// Get full path
	char abspath[ 256 ];
#ifdef WIN32
	_fullpath( abspath, ( filePath ).c_str(), MAX_PATH );
#else
	realpath( filePath.c_str(), abspath );
#endif

	auto endOfPath = filePath.find_last_of( "\\/" );
	fileName = filePath.substr( endOfPath + 1 );
	extension = fileName.substr( fileName.find_last_of( '.' ) );
	directory = filePath.substr( 0, endOfPath + 1 );
	fullPath = abspath;
	localPath = filePath;
}