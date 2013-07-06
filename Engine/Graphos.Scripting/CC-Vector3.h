#ifndef __CC_VECTOR3
#define __CC_VECTOR3

#include "Transform.h"
#include "Vector2.h"
#include "Vector3.h"

#include <v8\v8.h>

#include "cvv8\ClassCreator.hpp"

namespace cvv8
{
	CVV8_TypeName_DECL((Vector3));

	// Define Constructors
	typedef Signature<Vector3 (
		CtorForwarder<Vector3*()>,
		CtorForwarder<Vector3*( float, float, float )>,
		CtorForwarder<Vector3*( const Vector3& )>
		)> BoundNativeVector3Ctors;

	template <>
	struct ClassCreator_InternalFields<Vector3>
		: ClassCreator_InternalFields_Base<Vector3>
	{};

	template <>
	struct ClassCreator_SearchPrototypeForThis<Vector3> : Opt_Bool<true>
	{};

	template <>
	class ClassCreator_Factory<Vector3>
		: public ClassCreator_Factory_Dispatcher<Vector3, CtorArityDispatcher<BoundNativeVector3Ctors>>
	{
	public:
		static Vector3* Create( v8::Persistent<v8::Object> & jsSelf, v8::Arguments const & argv );
		static void Delete( Vector3* obj );
	};

	template <>
	struct ClassCreator_WeakWrap<Vector3>
	{
		typedef TypeInfo<Vector3>::NativeHandle NativeHandle;
		static void PreWrap( v8::Persistent<v8::Object> const &, v8::Arguments const & );
		static void Wrap( v8::Persistent<v8::Object> const &, NativeHandle );
		static void Unwrap( v8::Handle<v8::Object> const &, NativeHandle );
	};

	template <>
	struct ClassCreator_SetupBindings<Vector3>
	{
		static void Initialize( v8::Handle<v8::Object> const & target );
	};


	template <>
	struct JSToNative<Vector3>
		: JSToNative_ClassCreator<Vector3> { };

	template <>
	struct NativeToJS<Vector3> : NativeToJSMap<Vector3>::NativeToJSImpl { };

} /* namespace */

#endif//__CC_VECTOR3