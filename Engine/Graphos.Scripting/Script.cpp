#include "Script.h"
#include "GameObject.h"
#include "Time.h"

#include <iostream>

using namespace v8;
using namespace std;

bool Graphos::Core::Script::Update( void )
{
	//instance.InvokeAsync( WSLit( "UpdateTransformS" ), JSArray() );

	Handle<Value> args[ 1 ];
	args[ 0 ] = Number::New( Time::Get().GetDeltaTime() );

	TryCatch tc;
	updateFunction->Call( instance, 1, args );

	//if( tc.HasCaught() )
	//	throw runtime_error( string( "An exception has been thrown in JavaScript: " + string( *String::AsciiValue( tc.Message()->GetSourceLine() ) ) + "\nStack trace:\n" + string( *String::AsciiValue( tc.StackTrace()->ToString() ) ) ) );

	//instance.InvokeAsync( WSLit( "Update" ), args );

	return true;
}