#ifndef __CC_TIME
#define __CC_TIME

#include "TimeController.h"

#include <v8\v8.h>

#include <cvv8\ClassCreator.hpp>
#include "NativeToJSMap_Graphos.h"

using namespace Graphos::Core;

namespace cvv8
{
	CVV8_TypeName_DECL((Time));

	// Define Constructors
	typedef Signature<Time (
		)> TimeCtors;

	template <>
	class ClassCreator_Factory<Time>
		: public ClassCreator_Factory_NativeToJSMap<Time, CtorArityDispatcher<TimeCtors>> { };

	template <>
	struct ClassCreator_SetupBindings<Time>
	{
		static void Initialize( v8::Handle<v8::Object> const & target );
	};

	template <>
	struct JSToNative<Time> : public JSToNative_ClassCreator<Time> { };

	template <>
	struct NativeToJS<Time> : public NativeToJSMap_Graphos<Time> { };
}

#endif//__CC_TIME
