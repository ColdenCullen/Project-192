#include <cvv8\XTo.hpp>
#include <cvv8\properties.hpp>
#include "ClassMapper.h"
#include "ShaderController.h"

using namespace v8;
using namespace Graphos::Core;

NAME_CLASS(ShaderController)

void cvv8::ClassCreator_SetupBindings<ShaderController>::Initialize( Handle<v8::Object> const & target )
{
	ClassCreator<ShaderController>& ShaderControllercc( ClassCreator<ShaderController>::Instance() );
	if( ShaderControllercc.IsSealed() )
	{
		ShaderControllercc.AddClassTo( TypeName<ShaderController>::Value, target );
		return;
	}

	// Set static methods
	Handle<FunctionTemplate> ctor( ShaderControllercc.CtorTemplate() );
	ctor->Set(
		String::New( "GetShader" ),
		FunctionTemplate::New( FunctionToInCa<IShader*( std::string ), &ShaderController::GetShader>::Call )->GetFunction() );

	ShaderControllercc.AddClassTo( TypeName<ShaderController>::Value, target );
};
