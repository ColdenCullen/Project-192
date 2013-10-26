#include <cvv8/XTo.hpp>
#include <cvv8/properties.hpp>
#include "ClassMapper.h"
#include "CgShader.h"

using namespace v8;
using namespace Graphos::Core;
using namespace Graphos::Graphics;

NAME_CLASS(CgShader)

void cvv8::ClassCreator_SetupBindings<CgShader>::Initialize( Handle<v8::Object> const & target )
{
	ClassCreator<CgShader>& cgShadercc( ClassCreator<CgShader>::Instance() );
	if( cgShadercc.IsSealed() )
	{
		cgShadercc.AddClassTo( TypeName<CgShader>::Value, target );
		return;
	}

	cgShadercc
		( "destroy", ClassCreator<CgShader>::DestroyObjectCallback )
		//( "Draw", ConstMethodToInCa<const CgShader, void (const Mesh&), &CgShader::Draw>::Call )
		//( "BindTexture", ConstMethodToInCa<const CgShader, void (const Texture&), &CgShader::BindTexture>::Call )
		;

	// Set static methods
	Handle<Function> ctor( cgShadercc.CtorFunction() );

	cgShadercc.AddClassTo( TypeName<CgShader>::Value, target );
};
