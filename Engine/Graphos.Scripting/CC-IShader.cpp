#include <cvv8\XTo.hpp>
#include <cvv8\properties.hpp>
#include "ClassMapper.h"
#include "IShader.h"

using namespace v8;
using namespace Graphos::Graphics;

NAME_CLASS(IShader)

void cvv8::ClassCreator_SetupBindings<IShader>::Initialize( Handle<v8::Object> const & target )
{
	ClassCreator<IShader>& IShadercc( ClassCreator<IShader>::Instance() );
	if( IShadercc.IsSealed() )
	{
		IShadercc.AddClassTo( TypeName<IShader>::Value, target );
		return;
	}

	IShadercc
		( "destroy", ClassCreator<IShader>::DestroyObjectCallback )
		//( "BuildConstBuffer", MethodToInCa<IShader, void (Arguments), &IShader::BuildConstBuffer>::Call )
		;

	IShadercc.Set( "BuildConstBuffer", &IShader::BuildConstBuffer );

	// Proxy accessor/mutator functions as JS properties

	// Set static methods
	Handle<Function> ctor( IShadercc.CtorFunction() );

	IShadercc.AddClassTo( TypeName<IShader>::Value, target );

	
};
