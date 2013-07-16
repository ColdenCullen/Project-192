#ifndef __CC_VECTOR3
#define __CC_VECTOR3

#include "Vector3.h"

#include <v8\v8.h>
#include "cvv8\ClassCreator.hpp"

using namespace Graphos::Math;

namespace cvv8
{
	CVV8_TypeName_DECL((Vector3));

	// Define Constructors
	typedef Signature<Vector3 (
		CtorForwarder<Vector3*()>,
		CtorForwarder<Vector3*( float, float, float)>,
		CtorForwarder<Vector3*( const Vector3& )>
		)> Vector3Ctors;

	template <>
	struct ClassCreator_InternalFields<Vector3>	: public ClassCreator_InternalFields_Base<Vector3> { };

	template <>
	struct ClassCreator_SearchPrototypeForThis<Vector3> : public Opt_Bool<true> { };

	template <>
	class ClassCreator_Factory<Vector3>
		: public ClassCreator_Factory_NativeToJSMap<Vector3, CtorArityDispatcher<Vector3Ctors>> { };

	template <>
	struct ClassCreator_WeakWrap<Vector3>
	{
		static void PreWrap( v8::Persistent<v8::Object> const &, v8::Arguments const & ) { }
		static void Wrap( v8::Persistent<v8::Object> const &, TypeInfo<Vector3>::NativeHandle ) { }
		static void Unwrap( v8::Handle<v8::Object> const &, TypeInfo<Vector3>::NativeHandle ) { }
	};

	template <>
	struct ClassCreator_SetupBindings<Vector3>
	{
		static void Initialize( v8::Handle<v8::Object> const & target );
	};


	template <>
	struct JSToNative<Vector3> : public JSToNative_ClassCreator<Vector3> { };

	template <>
	struct NativeToJS<Vector3> : public NativeToJSMap<Vector3>
	{
		v8::Handle<v8::Value> operator()( const Vector3& v ) const;
	};
}

#endif//__CC_VECTOR3