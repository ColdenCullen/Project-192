#ifndef __CC_Transform
#define __CC_Transform

#include "Transform.h"

#include <v8\v8.h>

#include "cvv8\ClassCreator.hpp"

using namespace Graphos::Math;

namespace cvv8
{
	CVV8_TypeName_DECL((Transform));

	// Define Constructors
	typedef Signature<Transform (
		CtorForwarder<Transform*()>
		)> TransformCtors;

	template <>
	struct ClassCreator_InternalFields<Transform>	: ClassCreator_InternalFields_Base<Transform> { };

	template <>
	struct ClassCreator_SearchPrototypeForThis<Transform> : Opt_Bool<true> { };

	template <>
	class ClassCreator_Factory<Transform>
		: public ClassCreator_Factory_NativeToJSMap<Transform, CtorArityDispatcher<TransformCtors>> { };

	template <>
	struct ClassCreator_WeakWrap<Transform>
	{
		static void PreWrap( v8::Persistent<v8::Object> const &, v8::Arguments const & ) { }
		static void Wrap( v8::Persistent<v8::Object> const &, TypeInfo<Transform>::NativeHandle ) { }
		static void Unwrap( v8::Handle<v8::Object> const &, TypeInfo<Transform>::NativeHandle ) { }
	};

	template <>
	struct ClassCreator_SetupBindings<Transform>
	{
		static void Initialize( v8::Handle<v8::Object> const & target );
	};

	template <>
	struct JSToNative<Transform> : JSToNative_ClassCreator<Transform> { };

	template <>
	struct NativeToJS<Transform> : NativeToJSMap<Transform>
	{
		v8::Handle<v8::Value> operator()( const Transform& v ) const;
	};
}

#endif//__CC_Transform