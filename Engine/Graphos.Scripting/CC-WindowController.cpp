#include <cvv8\XTo.hpp>
#include <cvv8\properties.hpp>
#include "ClassMapper.h"
#include "WindowController.h"

using namespace v8;
using namespace Graphos::Math;
using namespace Graphos::Graphics;

NAME_CLASS(WindowController)

void cvv8::ClassCreator_SetupBindings<WindowController>::Initialize( Handle<v8::Object> const & target )
{
	ClassCreator<WindowController>& WindowControllercc( ClassCreator<WindowController>::Instance() );
	if( WindowControllercc.IsSealed() )
	{
		WindowControllercc.AddClassTo( TypeName<WindowController>::Value, target );
		return;
	}

	WindowControllercc
		( "destroy", ClassCreator<WindowController>::DestroyObjectCallback )
		( "Initialize", MethodToInCa<WindowController, void( void ), &WindowController::Initialize>::Call )
		( "Shutdown", MethodToInCa<WindowController, void( void ), &WindowController::Shutdown>::Call )
		( "Resize", MethodToInCa<WindowController, void( void ), &WindowController::Resize>::Call )
		( "OpenWindow", MethodToInCa<WindowController, void( void ), &WindowController::OpenWindow>::Call )
		( "CloseWindow", MethodToInCa<WindowController, void( void ), &WindowController::CloseWindow>::Call )
		;

	// Proxy accessor/mutator functions as JS properties
	AccessorAdder Vector3acc( WindowControllercc.Prototype() );
	Vector3acc
		( "Width",
			MethodToGetter<WindowController, unsigned int( void ), &WindowController::GetWidth>::Get,
			ThrowingSetter::Set )
		( "Height",
			MethodToGetter<WindowController, unsigned int( void ), &WindowController::GetHeight>::Get,
			ThrowingSetter::Set )
		( "PerspectiveMatrix",
			MethodToGetter<WindowController, Matrix4&( void ), &WindowController::PerspectiveMatrix>::Get,
			ThrowingSetter::Set )
		( "OrthogonalMatrix",
			MethodToGetter<WindowController, Matrix4&( void ), &WindowController::OrthogonalMatrix>::Get,
			ThrowingSetter::Set )
		;

	// Set static methods
	Handle<FunctionTemplate> ctor( WindowControllercc.CtorTemplate() );
	ctor->Set(
		String::New( "Get" ),
		FunctionTemplate::New( FunctionToInCa<WindowController*( void ), &WindowController::Get>::Call )->GetFunction() );

	WindowControllercc.AddClassTo( TypeName<WindowController>::Value, target );
};
