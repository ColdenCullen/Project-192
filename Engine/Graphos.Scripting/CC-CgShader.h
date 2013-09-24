#ifndef __CC_CG_SHADER
#define __CC_CG_SHADER

#include "CgShader.h"

#include <v8\v8.h>

#include <cvv8\ClassCreator.hpp>
#include "NativeToJSMap_Graphos.h"

using namespace Graphos::Graphics;

namespace cvv8
{
	CVV8_TypeName_DECL((CgShader));

	// Define Constructors
	typedef Signature<CgShader (
		CtorForwarder<CgShader*( std::string )>,
		CtorForwarder<CgShader*( std::string, std::string )>
		)> CgShaderCtors;


	template <>
	class ClassCreator_Factory<CgShader>
		: public ClassCreator_Factory_NativeToJSMap<CgShader, CtorArityDispatcher<CgShaderCtors>> { };

	template <>
	struct ClassCreator_SetupBindings<CgShader>
	{
		static void Initialize( v8::Handle<v8::Object> const & target );
	};

	template <>
	struct JSToNative<CgShader> : JSToNative_ClassCreator<CgShader> { };

	template <>
	struct NativeToJS<CgShader> : NativeToJSMap_Graphos<CgShader> { };
}

#endif//__CC_CG_SHADER
