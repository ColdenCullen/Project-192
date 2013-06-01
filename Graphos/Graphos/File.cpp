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

// For error checking
#include <assert.h>

using namespace std;
using namespace Graphos::Core;

string File::ReadFile( string filePath )
{
	ifstream fileStream( filePath.c_str() );

	assert( fileStream );

	stringstream shaderData;
	shaderData << fileStream.rdbuf();
	fileStream.close();

	return shaderData.str();
}

File::FileList File::ScanDir( string dirPath )
{
	FileList files;
	stack<string> directories;
	string current;

	directories.push( "" );

	DIR* dir;
	dirent* ent;

	// Loop through directories
	while( directories.size() )
	{
		current = directories.top();
		directories.pop();

		// Open directory and check for validity
		assert( ( dir = opendir( string( dirPath + current ).c_str() ) ) != NULL );

		// Iterate through contents
		while( ( ent = readdir( dir ) ) != NULL )
		{	// If the name is longer than two (to filter out '.' and '..')
			if( ent->d_namlen > 2 )
			{	// If the dirent is a directory, push it on to the stack, else put it in the list
				if( ent->d_type == DT_DIR )
					directories.push( current + ent->d_name + "/" );
				else if( ent->d_type == DT_REG )
					files.push_back( File( current, ent->d_name) );
			}	
		}

		// Close dir
		closedir( dir );
	}

	return files;
}

File::File( string filePath )
{
	auto endOfPath = filePath.find_last_of( "\\/" );

	// If there is no (back)slash, then filePath is the name
	if( endOfPath == string::npos )
		Initialize( "", filePath );
	// Else, get the path
	else
		Initialize( filePath.substr( 0, endOfPath + 1 ), filePath.substr( endOfPath + 1 ) );
}

File::File( string path, string name )
{
	Initialize( path, name );
}

const string File::GetFullPath( void ) const
{
	return location + name;
}

const string File::GetContents( void ) const
{
	return File::ReadFile( GetFullPath() );
}

void File::Initialize( string p, string n )
{
	// Get full path
	char abspath[ 256 ];
#ifdef WIN32
	_fullpath( abspath, p.c_str(), MAX_PATH );
#else
	realpath( path.c_str(), abspath );
#endif

	location = abspath;
	name = n;
}