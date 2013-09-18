#ifndef __CLASS_MAPPER
#define __CLASS_MAPPER

#include "CC-Transform.h"
#include "CC-Vector3.h"

#include <v8\v8.h>

namespace Graphos
{
	namespace Scripting
	{
		class ClassMapper
		{
		public:
			static void BindGraphosTypes( v8::Handle<v8::Object>& dest )
			{
				cvv8::ClassCreator<Transform>::SetupBindings( dest );
				cvv8::ClassCreator<Vector3>::SetupBindings( dest );
			}
		};
	}
}

#endif//__CLASS_MAPPER