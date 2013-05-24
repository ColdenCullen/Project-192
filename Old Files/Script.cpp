#include "Script.h"
#include "GameObject.h"

#include <iostream>

using namespace Graphos;

bool Content::Script::Update( float deltaTime )
{
	//instance.InvokeAsync( WSLit( "UpdateTransformS" ), JSArray() );

	Handle<Value> args[ 1 ];
	args[ 0 ] = Number::New( deltaTime );

	updateFunction->Call( instance, 1, args );

	//instance.InvokeAsync( WSLit( "Update" ), args );

	return true;
}