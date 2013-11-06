#include "JsonObject.h"
#include "Vector3.h"

using namespace std;
using namespace Graphos;
using namespace Graphos::Math;
using namespace Graphos::Utility;

JsonObject* JsonObject::GetChildren( void )
{
	throw exception( "Not implemented." );
}

template<>
auto JsonObject::Get( string path )							-> Json::Value&
{
	if( path.size() == 0 )
		return node;

	std::string left;
	std::string right = path;
	int currentIndex;
	Json::Value* currentValue = &node;

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
auto JsonObject::Get( string path )							-> Json::Value
{
	return Get<Json::Value&>( path );
}

template<>
auto JsonObject::Get( string path )							-> JsonObject
{
	return JsonObject( Get<Json::Value>( path ) );
}

template<>
auto JsonObject::Get( string path )							-> int
{
	const Json::Value& val = Get<Json::Value>( path );

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
auto JsonObject::Get( string path )							-> unsigned int
{
	const Json::Value& val = Get<Json::Value>( path );

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
auto JsonObject::Get( string path )							-> float
{
	const Json::Value& val = Get<Json::Value>( path );

	if( val.isDouble() )
	{
		return static_cast<float>( val.asDouble() );
	}
	else
	{
		return static_cast<float>( atof( val.asCString() ) );
	}
}

template<>
auto JsonObject::Get( string path )							-> bool
{
	const Json::Value& val = Get<Json::Value>( path );

	if( val.isBool() )
	{
		return val.asBool();
	}
	else
	{
		return val.asString() == "true";
	}
}

template<>
auto JsonObject::Get( string path )							-> std::string
{
	return Get<Json::Value>( path ).asString();
}

template<>
auto JsonObject::Get( string path )							-> const char*
{
	return Get<Json::Value>( path ).asCString();
}

template<>
auto JsonObject::Get( string path )							-> std::string*
{
	Json::Value& node = Get<Json::Value>( path );

	if( node.isArray() )
	{
		std::string* toReturn = new std::string[ node.size() ];

		for( unsigned int ii = 0; ii < node.size(); ++ii )
			toReturn[ ii ] = node[ ii ].asString();

		return toReturn;
	}
	else
	{
		return nullptr;
	}
}

template<>
auto JsonObject::Get( string path )							-> Math::Vector3
{
	Json::Value root = Get<Json::Value>( path );

	return Math::Vector3(
			static_cast<float>( root.get( "x", root ).asDouble() ),
			static_cast<float>( root.get( "y", root ).asDouble() ),
			static_cast<float>( root.get( "z", root ).asDouble() )
		);
}
