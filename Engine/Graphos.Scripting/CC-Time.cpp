#include <cvv8\XTo.hpp>
#include <cvv8\properties.hpp>
#include "ClassMapper.h"
#include "TimeController.h"

using namespace v8;
using namespace Graphos::Core;

NAME_CLASS(Time)

void cvv8::ClassCreator_SetupBindings<Time>::Initialize( Handle<v8::Object> const & target )
{
	ClassCreator<Time>& Timecc( ClassCreator<Time>::Instance() );
	if( Timecc.IsSealed() )
	{
		Timecc.AddClassTo( TypeName<Time>::Value, target );
		return;
	}

	target->SetAccessor( String::New( "DeltaTime" ),
						FunctionToGetter<const gFloat(void), &Time::GetDeltaTime>::Get,
		  				ThrowingSetter::Set );
	target->SetAccessor( String::New( "TotalTime" ),
		  				FunctionToGetter<const gFloat(void), &Time::GetTotalTime>::Get,
		  				ThrowingSetter::Set );

	/*Timecc
		( "DeltaTime",
			FunctionToInCa<const gFloat( void ), &getDeltaTime>::Call )
		( "TotalTime",
			FunctionToInCa<const gFloat(void), &getTotalTime>::Call )
		;*/

	/*AccessorAdder Timeacc( Timecc.Prototype() );
	Timeacc
		( "DeltaTime",
			FunctionToGetter<const gFloat( void ), &getDeltaTime>::Get,
			ThrowingSetter::Set )
		( "TotalTime",
			FunctionToGetter<const gFloat(void), &getTotalTime>::Get,
			ThrowingSetter::Set )
		;*/

	// Set static methods
	/*
	Handle<Object> ctor( Timecc.CtorFunction() );
	ctor->SetAccessor( String::New( "DeltaTime" ),
						FunctionToGetter<const gFloat(void), &Time::GetDeltaTime>::Get,
						ThrowingSetter::Set );
	ctor->SetAccessor( String::New( "TotalTime" ),
						FunctionToGetter<const gFloat(void), &Time::GetTotalTime>::Get,
						ThrowingSetter::Set );
	*/

	Timecc.AddClassTo( TypeName<Time>::Value, target );
};
