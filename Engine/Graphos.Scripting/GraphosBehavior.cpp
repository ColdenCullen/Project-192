#include <iostream>
#include <cstdarg>

#include "GraphosBehavior.h"
#include "TimeController.h"
#include "OutputController.h"
#include "GameObjectCollection.h"
#include "ClassMapper.h"

using namespace v8;
using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Utility;

GraphosBehavior::GraphosBehavior( Persistent<Object> instance, GameObject* owner /*= nullptr */ )
	: IComponent( owner ), instance( instance )
{
	updateFunction = Handle<Function>::Cast( instance->Get( String::New( "Update" ) ) );

	if( !updateFunction->IsFunction() )
		OutputController::PrintMessage( OutputType::Error, "Invalid Update function." );
}

GraphosBehavior::~GraphosBehavior( void )
{

}

void GraphosBehavior::SetInitialValues( JsonObject initVals )
{
	initialValues = initVals;
}

void GraphosBehavior::Initialize( GameObjectCollection* objects )
{
	for( auto val : initialValues.node.getMemberNames() )
	{
		JsonObject current = initialValues.Get<JsonObject>( val );
		Handle<Value> toSet;

		if( current.node.isString() && current.Get<string>( "" ).find( "object:" ) != string::npos )
		{
			string objectName = current.Get<string>( "" ).substr( 7 );

			toSet = cvv8::CastToJS( objects->GetObjectByName( objectName ) );
		}
		else
		{
			toSet = current.Get<Handle<Value>>( "" );
		}


		instance->Set( String::New( val.c_str() ), toSet );
	}
}

void GraphosBehavior::Update( void )
{
	//*
	//updateFunction->Call( instance, 0, NULL );
	CallFunction( "OnUpdate" );
	/*/
	TryCatch tc;
	updateFunction->Call( instance, 0, NULL );

	if( tc.HasCaught() )
	{
		string exceptionName = string( *String::AsciiValue( tc.Message()->Get()->ToString() ) );
		string stackTrace = string( *String::AsciiValue( tc.StackTrace()->ToString() ) );
		string message = string( "An exception has been thrown in JavaScript: " + exceptionName + "\nStack trace:\n" + stackTrace );
		OutputController::PrintMessage( OutputType::OT_ERROR, message );
	}
	//*/
}

void GraphosBehavior::CallFunction( string name, ... )
{
	auto func = Handle<Function>::Cast( instance->Get( String::New( name.c_str() ) ) );

	if( !func->IsFunction() )
		OutputController::PrintMessage( OutputType::Error, "Invalid " + name + " function." );

	int count = 0;
	va_list args;
	va_start( args, count );
	Handle<Value>* vals;
	
	if( count )
	{
		vals = new Handle<Value>[ count ];

		for( int ii = 0; ii < count; ++ii )
		{
			vals[ ii ] = va_arg( args, Handle<Value> );
		}
	}
	else
	{
		vals = NULL;
	}

	va_end( args );

	func->Call( instance, count, vals );

	/*
	TryCatch tc;
	func->Call( instance, 0, NULL );

	if( tc.HasCaught() )
	{
		string exceptionName = string( *String::AsciiValue( tc.Message()->Get()->ToString() ) );
		string stackTrace = string( *String::AsciiValue( tc.StackTrace()->ToString() ) );
		string message = string( "An exception has been thrown in JavaScript: " + exceptionName + "\nStack trace:\n" + stackTrace );
		OutputController::PrintMessage( OutputType::OT_ERROR, message );
	}
	//*/
}
