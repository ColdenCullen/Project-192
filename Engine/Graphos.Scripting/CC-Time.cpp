#include "CC-Time.h"

#include "cvv8\XTo.hpp"
#include "cvv8\properties.hpp"

using namespace v8;

namespace cvv8
{
	CVV8_TypeName_IMPL((Time), "Time");

	void ClassCreator_SetupBindings<Time>::Initialize( Handle<v8::Object> const & target )
	{
		ClassCreator<Time>& Timecc( ClassCreator<Time>::Instance() );
		if( Timecc.IsSealed() )
		{
			Timecc.AddClassTo( TypeName<Time>::Value, target );
			return;
		}

		/*
		Timecc
			( "destroy", ClassCreator<Time>::DestroyObjectCallback )
			( "Equals", ConstMethodToInCa<const Time, bool (const Time&), &Time::Equals>::Call )
			( "Dot", ConstMethodToInCa<const Time, float (const Time&), &Time::Dot>::Call )
			( "Cross", ConstMethodToInCa<const Time, Time (const Time&), &Time::Cross>::Call )
			( "Add", ConstMethodToInCa<const Time, Time (const Time&), &Time::Add>::Call )
			;
		*/

		// Proxy accessor/mutator functions as JS properties
		/*
		AccessorAdder Timeacc( Timecc.Prototype() );
		Timeacc
			( "x",
			MemberToAccessors<const Time, float, &Time::x>::Get,
			MemberToAccessors<const Time, float, &Time::x>::Set )
			( "y",
			MemberToAccessors<const Time, float, &Time::y>::Get,
			MemberToAccessors<const Time, float, &Time::y>::Set )
			( "z",
			MemberToAccessors<const Time, float, &Time::z>::Get,
			MemberToAccessors<const Time, float, &Time::z>::Set )
			;
		*/

		// Set static methods
		Handle<Function> ctor( Timecc.CtorFunction() );
		ctor->SetAccessor( String::New( "DeltaTime" ),
			MethodToGetter<const Time, const float (void), &Time::GetDeltaTime>::Get,
			ThrowingSetter::Set );

		Timecc.AddClassTo( TypeName<Time>::Value, target );
	};

	Handle<Value> NativeToJS<Time>::operator()( const Time& v ) const
	{
		Handle<Object> toReturn;

		if( ( toReturn = GetJSObject( (void*)&v ) ).IsEmpty() )
		{	// If object does not exist in the JSMap, create it
			Handle<Value> params[] =
			{
				Number::New( v.GetDeltaTime() ),
			};

			toReturn = ClassCreator<Time>::Instance().NewInstance( 3, params )->ToObject();
		}

		return toReturn;
	}
} /* namespace */