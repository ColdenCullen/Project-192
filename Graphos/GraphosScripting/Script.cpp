#include "Script.h"
#include "GameObject.h"
#include "Time.h"

#include <iostream>

using namespace v8;

bool Graphos::Core::Script::Update( void )
{
	//instance.InvokeAsync( WSLit( "UpdateTransformS" ), JSArray() );

	Handle<Value> args[ 1 ];
	args[ 0 ] = Number::New( Time::Get().GetDeltaTime() );

	updateFunction->Call( instance, 1, args );

	//instance.InvokeAsync( WSLit( "Update" ), args );

	return true;
}