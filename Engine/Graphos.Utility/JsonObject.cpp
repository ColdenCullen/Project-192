#include "JsonObject.h"
#include "Vector3.h"

using namespace std;
using namespace Graphos;
using namespace Graphos::Math;
using namespace Graphos::Utility;

#pragma region GetData
template<>
Json::Value& JsonObject::GetValue<Json::Value&>( std::string path )
{
	if( path.size() == 0 )
		return object;

	std::string left;
	std::string right = path;
	int currentIndex;
	Json::Value* currentValue = &object;

	do
	{
		currentIndex = right.find( '.' );

		if( currentIndex != std::string::npos )
		{
			left = right.substr( 0, currentIndex );
			right = right.substr( currentIndex + 1, std::string::npos );
		}
		else
		{
			left = right;
		}

		if( ( *currentValue )[ left ].isNull() )
		{
			if( currentIndex == std::string::npos )
				( *currentValue )[ left ] = Json::Value();
			else
				( *currentValue )[ left ] = Json::Value( Json::objectValue );
			currentValue = &( *currentValue )[ left ];
		}
		else
		{
			currentValue = &( *currentValue )[ left ];
		}
	} while( currentIndex != std::string::npos );

	return *currentValue;
}

template<>
Json::Value JsonObject::GetValue<Json::Value>( std::string path )
{
	return GetValue<Json::Value&>( path );
}

template<>
JsonObject JsonObject::GetValue<JsonObject>( std::string path )
{
	return JsonObject( GetValue<Json::Value>( path ) );
}

template<>
int JsonObject::GetValue<int>( std::string path )
{
	const Json::Value& val = GetValue<Json::Value>( path );

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
unsigned int JsonObject::GetValue<unsigned int>( std::string path )
{
	const Json::Value& val = GetValue<Json::Value>( path );

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
float JsonObject::GetValue<float>( std::string path )
{
	const Json::Value& val = GetValue<Json::Value>( path );

	if( val.isUInt() )
	{
		return static_cast<float>( val.asDouble() );
	}
	else
	{
		return static_cast<float>( atof( val.asCString() ) );
	}
}
template<>
bool JsonObject::GetValue<bool>( std::string path )
{
	const Json::Value& val = GetValue<Json::Value>( path );

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
std::string JsonObject::GetValue<std::string>( std::string path )
{
	return GetValue<Json::Value>( path ).asString();
}
template<>
const char* JsonObject::GetValue<const char*>( std::string path )
{
	return GetValue<Json::Value>( path ).asCString();
}
template<>
std::string* JsonObject::GetValue<std::string*>( std::string path )
{
	Json::Value& node = GetValue<Json::Value>( path );

	if( node.isArray() )
	{
		std::string* toReturn = new std::string[ node.size() ];

		for( unsigned int ii = 0; ii < node.size(); ++ii )
			toReturn[ ii ] = node[ ii ].asString();

		return toReturn;
	}
}
template<>
Math::Vector3 JsonObject::GetValue<Math::Vector3>( std::string path )
{
	Json::Value root = GetValue<Json::Value>( path );

	return Math::Vector3(
		static_cast<float>( root.get( "x", root ).asDouble() ),
		static_cast<float>( root.get( "y", root ).asDouble() ),
		static_cast<float>( root.get( "z", root ).asDouble() )
		);
}
#pragma endregion
