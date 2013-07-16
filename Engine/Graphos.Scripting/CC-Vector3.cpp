#include "CC-Vector3.h"

#include "cvv8\XTo.hpp"
#include "cvv8\properties.hpp"

using namespace v8;

namespace cvv8
{
	CVV8_TypeName_IMPL((Vector3), "Vector3");

	void ClassCreator_SetupBindings<Vector3>::Initialize( Handle<v8::Object> const & target )
	{
		ClassCreator<Vector3>& Vector3cc( ClassCreator<Vector3>::Instance() );
		if( Vector3cc.IsSealed() )
		{
			Vector3cc.AddClassTo( TypeName<Vector3>::Value, target );
			return;
		}

		Vector3cc
			( "destroy", ClassCreator<Vector3>::DestroyObjectCallback )
			( "Equals", ConstMethodToInCa<const Vector3, bool (const Vector3&), &Vector3::Equals>::Call )
			( "Dot", ConstMethodToInCa<const Vector3, float (const Vector3&), &Vector3::Dot>::Call )
			( "Cross", ConstMethodToInCa<const Vector3, Vector3 (const Vector3&), &Vector3::Cross>::Call )
			( "Add", ConstMethodToInCa<const Vector3, Vector3 (const Vector3&), &Vector3::Add>::Call )
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

		// Set static methods
		Handle<Function> ctor( Vector3cc.CtorFunction() );
		ctor->Set( String::New( "TrippleProduct" ), FunctionTemplate::New( FunctionToInCa<Vector3 (const Vector3&, const Vector3&, const Vector3&), &Vector3::TripleProduct>::Call )->GetFunction() );

		Vector3cc.AddClassTo( TypeName<Vector3>::Value, target );
	};

	Handle<Value> NativeToJS<Vector3>::operator()( const Vector3& v ) const
	{
		Handle<Object> toReturn;

		if( !( toReturn = GetJSObject( (void*)&v ) ).IsEmpty() )
		{	// If the object exists, return it
			
		}
		else
		{	// If object does not exist in the JSMap, create it
			Handle<Value> params[] =
			{
				Number::New( v.x ),
				Number::New( v.y ),
				Number::New( v.z )
			};

			toReturn = ClassCreator<Vector3>::Instance().NewInstance( 3, params )->ToObject();
		}

		return toReturn;
	}
} /* namespace */