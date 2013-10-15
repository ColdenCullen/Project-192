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

	// Set static methods
	Handle<Function> ctor( Timecc.CtorFunction() );
	ctor->SetAccessor( String::New( "DeltaTime" ),
						FunctionToGetter<const float(void), &Time::GetDeltaTime>::Get,
						ThrowingSetter::Set );
	ctor->SetAccessor( String::New( "TotalTime" ),
						FunctionToGetter<const float(void), &Time::GetTotalTime>::Get,
						ThrowingSetter::Set );

	Timecc.AddClassTo( TypeName<Time>::Value, target );
};
