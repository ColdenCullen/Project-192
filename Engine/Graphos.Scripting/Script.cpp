#include "Script.h"
#include "TimeController.h"

#include <iostream>
#include "OutputController.h"

using namespace v8;
using namespace std;
using namespace Graphos::Core;

void Graphos::Core::Script::Update( void )
{
	//Handle<Value> args[ 1 ];
	//args[ 0 ] = Number::New( Time::GetDeltaTime() );
	//TryCatch tc;

	/*
	updateFunction->Call( instance, 0, NULL );

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

Graphos::Core::Script::Script( Handle<Object> instance, GameObject* owner /*= nullptr */ )
	: IComponent( owner ), instance( instance )
{
	updateFunction = Handle<Function>::Cast( instance->Get( String::New( "Update" ) ) );

	if( !updateFunction->IsFunction() )
		OutputController::PrintMessage( OutputType::OT_ERROR, "Invalid Update function." );
}
