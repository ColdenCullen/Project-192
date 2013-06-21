#include "Config.h"

#include "File.h"

#include <string>

using namespace std;
using namespace Graphos::Core;

void Config::LoadSettings( void )
{
	Json::Reader reader;

	if( !reader.parse( File::ReadFile( "Resources/Config/Config.json" ), config ) )
		throw exception( "Error reading JSON" );
}

Json::Value& Config::GetValueAtPath( std::string path )
{
	std::string left;
	std::string right = path;
	int currentIndex;
	Json::Value* currentValue = &config;

	do
	{
		currentIndex = right.find( '.' );

		if( currentIndex != std::string::npos )
		{
			left = right.substr( 0, currentIndex );
			right = right.substr( currentIndex + 1, string::npos );
		}
		else
		{
			left = right;
		}

		currentValue = &( *currentValue )[ left ];
	} while( currentIndex != string::npos );

	return *currentValue;
}

#pragma region GetData
#if defined( __APPLE__ )
template<>
int Config::GetData<int>( string path )
{
	const Json::Value& val = GetValueAtPath( path );

	if( val.isInt() )
	{
		return val.asInt();
	}
	else
	{
		return atoi( val.asCString() );
	}
}
template<>
unsigned int Config::GetData<unsigned int>( string path )
{
	const Json::Value& val = GetValueAtPath( path );

	if( val.isUInt() )
	{
		return val.asUInt();
	}
	else
	{
		return static_cast<unsigned int>( atoi( val.asCString() ) );
	}
}
template<>
float Config::GetData<float>( string path )
{
	const Json::Value& val = GetValueAtPath( path );

	if( val.isUInt() )
	{
		return static_cast<float>( val.asDouble() );
	}
	else
	{
		return atof( val.asCString() );
	}
}
template<>
bool Config::GetData<bool>( string path )
{
	const Json::Value& val = GetValueAtPath( path );

	if( val.isUInt() )
	{
		return val.asBool();
	}
	else
	{
		return val.asString() == "true";
	}
}
template<>
string Config::GetData<string>( string path )
{
	return GetValueAtPath( path ).asString();
}
template<>
const char* Config::GetData<const char*>( string path )
{
	return GetValueAtPath( path ).asCString();
}
template<>
Vector3	Config::GetData<Vector3>( string path )
{
	Json::Value root = GetValueAtPath( path );

	return Vector3(
		static_cast<float>( root.get( "x", root ).asDouble() ),
		static_cast<float>( root.get( "y", root ).asDouble() ),
		static_cast<float>( root.get( "z", root ).asDouble() )
		);
}
#endif
#pragma endregion