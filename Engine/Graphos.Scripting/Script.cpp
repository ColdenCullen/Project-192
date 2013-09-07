#include "Script.h"
#include "GameObject.h"
#include "Time.h"

#include <iostream>

using namespace v8;
using namespace std;

void Graphos::Core::Script::Update( void )
{
	//Handle<Value> args[ 1 ];
	//args[ 0 ] = Number::New( ISingleton<Time>::Get().GetDeltaTime() );
	
	TryCatch tc;
	updateFunction->Call( instance, 0, NULL );

	/*
	if( tc.HasCaught() )
	{
		string exceptionName = string( *String::AsciiValue( tc.Message()->GetSourceLine() ) );
		string stackTrace = string( *String::AsciiValue( tc.StackTrace()->ToString() ) );
		string message = string( "An exception has been thrown in JavaScript: " + exceptionName + "\nStack trace:\n" + stackTrace );
		throw runtime_error( message );
	}
	*/
}