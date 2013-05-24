#define delete_s(x) if( x != nullptr ) { delete x; x = nullptr; }

#if defined( _USE_READ_FILE ) || defined( _USE_SCAN_DIR )

#ifndef __HELPERS
#define __HELPERS

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <stack>
#include <exception>

#if defined( _WIN32 )
 #include <windirent.h>
#elif defined( __APPLE__ )
 #include <dirent.h>
#endif

using namespace std;

struct Helpers
{
#ifdef _USE_READ_FILE
#undef _USE_READ_FILE
	// Reads a file to a string
	static string ReadFile( string fileName )
	{
		ifstream fileStream( fileName.c_str() );
		if( !fileStream )
		{
			throw new exception( "Error reading file" );
			return "";
		}

		stringstream shaderData;
		shaderData << fileStream.rdbuf();
		fileStream.close();

		return shaderData.str();
	}
#endif//_USE_READ_FILE

#ifdef _USE_SCAN_DIR
#undef _USE_SCAN_DIR
	static unordered_map<string, string> ScanDir( string dirPath )
	{
		unordered_map<string, string> files;
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

			// Open directory
			if( ( dir = opendir( string( dirPath + current ).c_str() ) ) != NULL )
			{
				// Iterate through contents
				while( ( ent = readdir( dir ) ) != NULL )
				{
					if( ent->d_namlen > 2 )
					{
						if( ent->d_type == DT_DIR )
							directories.push( current + ent->d_name + "/" );
						else if( ent->d_namlen > 4 )
							files[ string( ent->d_name ) ] = current;
					}	
				}

				// Close dir
				closedir( dir );
			}
			else
			{
				throw new exception( "Error opening directory" );
			}
		}

		return files;
	}
#endif//_USE_SCAN_DIR
};

#endif//__HELPERS

#endif