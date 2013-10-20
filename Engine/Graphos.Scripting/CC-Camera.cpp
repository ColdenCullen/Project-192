#include <cvv8\XTo.hpp>
#include <cvv8\properties.hpp>
#include "ClassMapper.h"
#include "Camera.h"

using namespace v8;
using namespace Graphos::Math;
using namespace Graphos::Core;

NAME_CLASS(Camera)

void cvv8::ClassCreator_SetupBindings<Camera>::Initialize( Handle<v8::Object> const & target )
{
	ClassCreator<Camera>& Cameracc( ClassCreator<Camera>::Instance() );
	if( Cameracc.IsSealed() )
	{
		Cameracc.AddClassTo( TypeName<Camera>::Value, target );
		return;
	}

	Cameracc
		( "destroy", ClassCreator<Camera>::DestroyObjectCallback )
		( "GetViewMatrix", MethodToInCa<Camera, Matrix4 (void), &Camera::GetViewMatrix>::Call )
		;

	// Set static methos
	Handle<Function> ctor( Cameracc.CtorFunction() );

	Cameracc.AddClassTo( TypeName<Camera>::Value, target );

	
};
