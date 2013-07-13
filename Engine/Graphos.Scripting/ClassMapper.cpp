#include "ClassMapper.h"
#include "CC-Vector3.h"

void Graphos::Scripting::ClassMapper::BindGraphosTypes( v8::Handle<v8::Object>& dest )
{
#define INIT_TYPE(type) cvv8::ClassCreator<type>::SetupBindings( dest )

	INIT_TYPE(Vector3);

#undef INIT_TYPE
}
