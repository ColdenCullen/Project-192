#ifndef __CC_TRANSFORM
#define __CC_TRANSFORM

#include "Transform.h"

#include <v8\v8.h>

#include <cvv8\ClassCreator.hpp>
#include "NativeToJSMap_Graphos.h"

using namespace Graphos::Math;

namespace cvv8
{
	CVV8_TypeName_DECL((Transform));

	// Define Constructors
	typedef Signature<Transform (
		CtorForwarder<Transform*()>
		)> TransformCtors;


	template <>
	class ClassCreator_Factory<Transform>
		: public ClassCreator_Factory_NativeToJSMap<Transform, CtorArityDispatcher<TransformCtors>> { };

	template <>
	struct ClassCreator_SetupBindings<Transform>
	{
		static void Initialize( v8::Handle<v8::Object> const & target );
	};

	template <>
	struct JSToNative<Transform> : JSToNative_ClassCreator<Transform> { };

	template <>
	struct NativeToJS<Transform> : NativeToJSMap_Graphos<Transform> { };
}

#endif//__CC_TRANSFORM
