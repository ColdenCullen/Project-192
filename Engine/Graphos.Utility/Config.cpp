#include "Config.h"

#include "File.h"

#include <string>

using namespace std;
using namespace Graphos;
using namespace Graphos::Utility;

void Config::Initialize( void )
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

Json::Value Config::config;

#pragma region GetData
template<>
int Config::GetData<int>( std::string path )
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
unsigned int Config::GetData<unsigned int>( std::string path )
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
float Config::GetData<float>( std::string path )
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
bool Config::GetData<bool>( std::string path )
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
std::string Config::GetData<std::string>( std::string path )
{
	return GetValueAtPath( path ).asString();
}
template<>
const char* Config::GetData<const char*>( std::string path )
{
	return GetValueAtPath( path ).asCString();
}
template<>
std::string* Config::GetData<std::string*>( std::string path )
{
	Json::Value& node = GetValueAtPath( path );

	if( node.isArray() )
	{
		std::string* toReturn = new std::string[ node.size() ];

		for( int ii = 0; ii < node.size(); ++ii )
			toReturn[ ii ] = node[ ii ].asString();

		return toReturn;
	}
}
template<>
Math::Vector3 Config::GetData<Math::Vector3>( std::string path )
{
	Json::Value root = GetValueAtPath( path );

	return Math::Vector3(
		static_cast<float>( root.get( "x", root ).asDouble() ),
		static_cast<float>( root.get( "y", root ).asDouble() ),
		static_cast<float>( root.get( "z", root ).asDouble() )
		);
}
#pragma endregion
