#include "CC-Vector3.h"

#include "cvv8\XTo.hpp"
#include "cvv8\properties.hpp"

namespace cvv8
{
	CVV8_TypeName_IMPL((Vector3),"Vector3");

#if 0 /* needed? */
	template <>
	const void * ClassCreator_TypeID<Vector3>::Value = TypeName<Vector3 >::Value;
#endif

	void ClassCreator_WeakWrap<Vector3>::PreWrap( v8::Persistent<v8::Object> const &, v8::Arguments const & )
	{
		return;
	}
	void ClassCreator_WeakWrap<Vector3>::Wrap( v8::Persistent<v8::Object> const &, NativeHandle )
	{
		return;
	}
	void ClassCreator_WeakWrap<Vector3>::Unwrap( v8::Handle<v8::Object> const &, NativeHandle )
	{
		return;
	}

	Vector3* ClassCreator_Factory<Vector3>::Create( v8::Persistent<v8::Object>& jsSelf, v8::Arguments const& argv )
	{
		Vector3* b = CtorArityDispatcher<BoundNativeVector3Ctors>::Call( argv );
		if( b ) NativeToJSMap<Vector3>::Insert( jsSelf, b );

		return b;
	}

	void ClassCreator_Factory<Vector3 >::Delete( Vector3* obj )
	{
		if(obj) delete obj;
	}

	void ClassCreator_SetupBindings<Vector3>::Initialize( v8::Handle<v8::Object> const & target )
	{
		ClassCreator<Vector3>& Vector3cc( ClassCreator<Vector3>::Instance() );
		if( Vector3cc.IsSealed() )
		{
			Vector3cc.AddClassTo( TypeName<Vector3>::Value, target );
			return;
		}

#define CATCHER InCaCatcher_std /* convenience macro */

		Vector3cc
			( "destroy", ClassCreator<Vector3>::DestroyObjectCallback )
			//( "Dot", MethodToInCa<const Vector3, float (const Vector3&), &Vector3::Dot>::Call )
			( "Cross", MethodToInCa<const Vector3, Vector3 (const Vector3&), &Vector3::Cross>::Call )
			//( "Equals", ConstMethodToInCa<const Vector3, bool (const Vector3&), &Vector3::operator==>::Call )
			;

		// Proxy accessor/mutator functions as JS properties
		AccessorAdder Vector3acc( Vector3cc.Prototype() );
		Vector3acc
			( "x",
				MemberToAccessors<const Vector3, float, &Vector3::x>::Get,
				MemberToAccessors<const Vector3, float, &Vector3::x>::Set )
			( "y",
				MemberToAccessors<const Vector3, float, &Vector3::y>::Get,
				MemberToAccessors<const Vector3, float, &Vector3::y>::Set )
			( "z",
				MemberToAccessors<const Vector3, float, &Vector3::z>::Get,
				MemberToAccessors<const Vector3, float, &Vector3::z>::Set )
			;

#if 0
		// Set up properties on the ctor...
		v8::Handle<v8::Function> ctor( Vector3cc.CtorFunction() );
		// then use ctor->Set() and friends.
		// These MUST come after your prototype-level bindings (don't ask me why
		
#endif
#undef CATCHER
			Vector3cc.AddClassTo( TypeName<Vector3>::Value, target );
		return;

	};
} /* namespace */