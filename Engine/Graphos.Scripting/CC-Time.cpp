//#include "CC-Time.h"
//
//#include "cvv8\XTo.hpp"
//#include "cvv8\properties.hpp"
//
//using namespace v8;
//
//namespace cvv8
//{
//	CVV8_TypeName_IMPL((Time), "Time");
//
//	void ClassCreator_SetupBindings<Time>::Initialize( Handle<v8::Object> const & target )
//	{
//		ClassCreator<Time>& Timecc( ClassCreator<Time>::Instance() );
//		if( Timecc.IsSealed() )
//		{
//			Timecc.AddClassTo( TypeName<Time>::Value, target );
//			return;
//		}
//
//		Timecc
//		( "destroy", ClassCreator<Time>::DestroyObjectCallback )
//		( "Equals", ConstMethodToInCa<const Time, bool (const Time&), &Time::Equals>::Call )
//		( "Dot", ConstMethodToInCa<const Time, float (const Time&), &Time::Dot>::Call )
//		( "Cross", ConstMethodToInCa<const Time, Time (const Time&), &Time::Cross>::Call )
//		( "Add", ConstMethodToInCa<const Time, Time (const Time&), &Time::Add>::Call )
//		;
//
//		// Proxy accessor/mutator functions as JS properties
//		AccessorAdder Timeacc( Timecc.Prototype() );
//		Timeacc
//			( "DeltaTime",
//			MethodToGetter<const Time, float, &Time::GetDeltaTime>::Get,
//			ThrowingSetter::Set )
//			;
//
//		// Set static methods
//		Handle<Function> ctor( Timecc.CtorFunction() );
//		ctor->SetAccessor( String::New( "DeltaTime" ), MethodToGetter<const Time, float (void), &Time::GetDeltaTime>::Get, ThrowingSetter::Set );
//
//		Timecc.AddClassTo( TypeName<Time>::Value, target );
//	};
//} /* namespace */