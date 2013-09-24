#include "CC-CgShader.h"

using namespace Graphos::Core;
using namespace Graphos::Graphics;

#include "cvv8\XTo.hpp"
#include "cvv8\properties.hpp"

using namespace v8;

namespace cvv8
{
	CVV8_TypeName_IMPL((CgShader), "CgShader");

	void ClassCreator_SetupBindings<CgShader>::Initialize( Handle<v8::Object> const & target )
	{
		ClassCreator<CgShader>& cgShadercc( ClassCreator<CgShader>::Instance() );
		if( cgShadercc.IsSealed() )
		{
			cgShadercc.AddClassTo( TypeName<CgShader>::Value, target );
			return;
		}

		cgShadercc
			( "destroy", ClassCreator<CgShader>::DestroyObjectCallback )
			( "Draw", ConstMethodToInCa<const CgShader, void (const Mesh&), &CgShader::Draw>::Call )
			( "BindTexture", ConstMethodToInCa<const CgShader, void (const Texture&), &CgShader::BindTexture>::Call )
			//( "Cross", ConstMethodToInCa<const CgShader, CgShader (const CgShader&), &CgShader::Cross>::Call )
			//( "Add", ConstMethodToInCa<const CgShader, CgShader (const CgShader&), &CgShader::Add>::Call )
			;

		// Set static methods
		Handle<Function> ctor( cgShadercc.CtorFunction() );
		//ctor->Set( String::New( "TripleProduct" ), FunctionTemplate::New( FunctionToInCa<Vector3 (const Vector3&, const Vector3&, const Vector3&), &Vector3::TripleProduct>::Call )->GetFunction() );

		cgShadercc.AddClassTo( TypeName<CgShader>::Value, target );
	};
} /* namespace */
