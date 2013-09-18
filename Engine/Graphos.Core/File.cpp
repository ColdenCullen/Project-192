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
using namespace Graphos::Core;

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
					files.push_back( File( dirPath, currentLocal, ent->d_name) );
				}
			}	
		}

		// Close dir
		closedir( dir );
	}

	return files;
}
#pragma endregion

#pragma region Not Static
File::File( string filePath )
{
	auto endOfPath = filePath.find_last_of( "\\/" );

	// If there is no (back)slash, then filePath is the name
	if( endOfPath == string::npos )
		Initialize( "", filePath, filePath );
	// Else, get the path
	else
		Initialize( filePath.substr( 0, endOfPath + 1 ), filePath.substr( endOfPath + 1 ), filePath.substr( endOfPath + 1 ) );
}

File::File( string path, string name )
{
	Initialize( path, name, name );
}

File::File( std::string path, std::string localPath, std::string name )
{
	Initialize( path, localPath, name );
}

void File::Initialize( string path, string lp, string name )
{
	// Get full path
	char abspath[ 256 ];
#ifdef WIN32
	_fullpath( abspath, ( path + lp ).c_str(), MAX_PATH );
#else
	realpath( path.c_str(), abspath );
#endif

	localPath = lp;
	fullPath = abspath;
	fileName = name;
}
#pragma endregion