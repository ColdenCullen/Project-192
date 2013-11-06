#include <iostream>
#include <cstdarg>

#include "Script.h"
#include "TimeController.h"
#include "OutputController.h"

using namespace v8;
using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Utility;

Graphos::Core::Script::Script( Persistent<Object> instance, GameObject* owner /*= nullptr */ )
	: IComponent( owner ), instance( instance )
{
	updateFunction = Handle<Function>::Cast( instance->Get( String::New( "Update" ) ) );

	if( !updateFunction->IsFunction() )
		OutputController::PrintMessage( OutputType::Error, "Invalid Update function." );
}

Graphos::Core::Script::~Script( void )
{

}

void Graphos::Core::Script::Update( void )
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

void Graphos::Core::Script::CallFunction( string name, ... )
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
