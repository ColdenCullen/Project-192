#include <v8.h>

#include "JsonObject.h"
#include "Vector3.h"

using namespace v8;
using namespace std;
using namespace Graphos;
using namespace Graphos::Math;
using namespace Graphos::Utility;

#pragma region Get
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
auto JsonObject::Get( std::string path )					-> Handle<Value>
{
	auto value = Get<Json::Value&>( path );
	Handle<Object> toReturn;

	switch( value.type() )
	{
	case Json::intValue:
	case Json::uintValue:
		return Integer::New( value.asInt() );
	case Json::booleanValue:
		return Boolean::New( value.asBool() );
	case Json::stringValue:
		return String::New( value.asCString() );
	case Json::realValue:
		return Number::New( value.asDouble() );
	case Json::arrayValue:
		toReturn = Array::New();

		for( unsigned int ii = 0; ii < node.getMemberNames().size(); ++ii )
			toReturn->Set( ii, Get<Handle<Value>>( node.getMemberNames()[ ii ] ) );

		return toReturn;
	case Json::objectValue:
		toReturn = Object::New();

		for( string prop : value.getMemberNames() )
			toReturn->Set( String::New( prop.c_str() ), Get<Handle<Value>>( path + "." + prop ) );

		return toReturn;
	}
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
#pragma endregion

vector<JsonObject> JsonObject::GetChildren( void )
{
	vector<JsonObject> children;

	for( auto prop : node.getMemberNames() )
		children.push_back( Get<JsonObject>( prop ) );

	return children;
}
