#include <cvv8\XTo.hpp>
#include <cvv8\properties.hpp>
#include "ClassMapper.h"
#include "WindowController.h"

using namespace v8;
using namespace Graphos::Math;
using namespace Graphos::Graphics;

NAME_CLASS(IPlatformWindowController)

void cvv8::ClassCreator_SetupBindings<IPlatformWindowController>::Initialize( Handle<v8::Object> const & target )
{
	ClassCreator<IPlatformWindowController>& WindowControllercc( ClassCreator<IPlatformWindowController>::Instance() );
	if( WindowControllercc.IsSealed() )
	{
		WindowControllercc.AddClassTo( TypeName<IPlatformWindowController>::Value, target );
		return;
	}

	WindowControllercc
		( "destroy", ClassCreator<IPlatformWindowController>::DestroyObjectCallback )
		( "Initialize", MethodToInCa<IPlatformWindowController, void( void ), &IPlatformWindowController::Initialize>::Call )
		( "Shutdown", MethodToInCa<IPlatformWindowController, void( void ), &IPlatformWindowController::Shutdown>::Call )
		( "Resize", MethodToInCa<IPlatformWindowController, void( void ), &IPlatformWindowController::Resize>::Call )
		( "OpenWindow", MethodToInCa<IPlatformWindowController, void( void ), &IPlatformWindowController::OpenWindow>::Call )
		( "CloseWindow", MethodToInCa<IPlatformWindowController, void( void ), &IPlatformWindowController::CloseWindow>::Call )
		;

	// Proxy accessor/mutator functions as JS properties
	AccessorAdder Vector3acc( WindowControllercc.Prototype() );
	Vector3acc
		( "Width",
			MethodToGetter<IPlatformWindowController, unsigned int( void ), &IPlatformWindowController::GetWidth>::Get,
			ThrowingSetter::Set )
		( "Height",
			MethodToGetter<IPlatformWindowController, unsigned int( void ), &IPlatformWindowController::GetHeight>::Get,
			ThrowingSetter::Set )
		( "PerspectiveMatrix",
			MethodToGetter<IPlatformWindowController, Matrix4&( void ), &IPlatformWindowController::PerspectiveMatrix>::Get,
			ThrowingSetter::Set )
		( "OrthogonalMatrix",
			MethodToGetter<IPlatformWindowController, Matrix4&( void ), &IPlatformWindowController::OrthogonalMatrix>::Get,
			ThrowingSetter::Set )
		;

	// Set static methods
	Handle<Function> ctor( WindowControllercc.CtorFunction() );
	ctor->Set(
		String::New( "Get" ),
		FunctionTemplate::New( FunctionToInCa<IPlatformWindowController*( void ), &WindowController::Get>::Call )->GetFunction() );

	WindowControllercc.AddClassTo( TypeName<WindowController>::Value, target );
};
