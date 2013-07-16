#include "ClassMapper.h"

#include "CC-Transform.h"
#include "CC-Vector3.h"

#include <cvv8\ClassCreator.hpp>

using namespace Graphos::Math;

void Graphos::Scripting::ClassMapper::BindGraphosTypes( v8::Handle<v8::Object>& dest )
{
	cvv8::ClassCreator<Transform>::SetupBindings( dest );
	cvv8::ClassCreator<Vector3>::SetupBindings( dest );
	//cvv8::ClassCreator<Time>::SetupBindings( dest );
}
