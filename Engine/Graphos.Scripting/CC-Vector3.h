#ifndef __CC_VECTOR3
#define __CC_VECTOR3

#include "Transform.h"
#include "Vector2.h"
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
	struct ClassCreator_InternalFields<Vector3>	: ClassCreator_InternalFields_Base<Vector3> { };

	template <>
	struct ClassCreator_SearchPrototypeForThis<Vector3> : Opt_Bool<true> { };

	template <>
	class ClassCreator_Factory<Vector3>
		: public ClassCreator_Factory_Dispatcher<Vector3, CtorArityDispatcher<Vector3Ctors>>
	{
	public:
		static Vector3* Create( v8::Persistent<v8::Object> & jsSelf, v8::Arguments const & argv );
		static void Delete( Vector3* obj );
	};

	template <>
	struct ClassCreator_WeakWrap<Vector3>
	{
		static void PreWrap( v8::Persistent<v8::Object> const &, v8::Arguments const & );
		static void Wrap( v8::Persistent<v8::Object> const &, TypeInfo<Vector3>::NativeHandle );
		static void Unwrap( v8::Handle<v8::Object> const &, TypeInfo<Vector3>::NativeHandle );
	};

	template <>
	struct ClassCreator_SetupBindings<Vector3>
	{
		static void Initialize( v8::Handle<v8::Object> const & target );
	};


	template <>
	struct JSToNative<Vector3> : JSToNative_ClassCreator<Vector3> { };

	template <>
	struct NativeToJS<Vector3> : NativeToJSMap<Vector3>
	{
		v8::Handle<v8::Value> operator()( const Vector3& v ) const
		{
			v8::Handle<v8::Value> params[] =
			{
				v8::NumberObject::New( v.x ),
				v8::NumberObject::New( v.y ),
				v8::NumberObject::New( v.z )
			};

			Vector3* test;

			auto result = ClassCreator<Vector3>::Instance().NewInstance( 3, params, test )->ToObject();

			if( !( *test == v ) )
				throw exception( "VEC3'S CAST'S BROKE YO" );

			//result->SetInternalField( ClassCreator_InternalFields<Vector3>::NativeIndex, v8::External::New( (void*)&v ) );

			return result;
		}
	};

} /* namespace */

#endif//__CC_VECTOR3