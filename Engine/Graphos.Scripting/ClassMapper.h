#ifndef __CLASS_MAPPER
#define __CLASS_MAPPER

#include <v8\v8.h>

namespace Graphos
{
	namespace Scripting
	{
		class ClassMapper
		{
		public:
			static void BindGraphosTypes( v8::Handle<v8::Object>& dest );
		};
	}
}

#endif//__CLASS_MAPPER