#ifndef __CC_VECTOR3
#define __CC_VECTOR3

#include "Vector3.h"

#include <v8\v8.h>
#include <cvv8\ClassCreator.hpp>
#include "NativeToJSMap_Graphos.h"

using namespace Graphos::Math;

namespace cvv8
{
	CVV8_TypeName_DECL((Vector3));

	// Define Constructors
	typedef Signature<Vector3 (
		CtorForwarder<Vector3*()>,
		CtorForwarder<Vector3*( float, float, float )>,
		CtorForwarder<Vector3*( const Vector3& )>
		)> Vector3Ctors;

	template <>
	class ClassCreator_Factory<Vector3>
		: public ClassCreator_Factory_NativeToJSMap<Vector3, CtorArityDispatcher<Vector3Ctors>> { };

	template <>
	struct ClassCreator_SetupBindings<Vector3>
	{
		static void Initialize( v8::Handle<v8::Object> const & target );
	};

	template <>
	struct JSToNative<Vector3> : public JSToNative_ClassCreator<Vector3> { };

	template <>
	struct NativeToJS<Vector3> : public NativeToJSMap_Graphos<Vector3> { };
}

#endif//__CC_VECTOR3