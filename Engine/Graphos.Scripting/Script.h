#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include <string>
#include <v8\v8.h>

#include "IComponent.h"

namespace Graphos
{
	namespace Core
	{
		class Script : public IComponent
		{
		public:
								Script( v8::Local<v8::Object> instance, GameObject* owner = nullptr )
									: instance( instance ), IComponent( owner ), updateFunction( v8::Handle<v8::Function>::Cast( instance->Get( v8::String::New( "Update" ) ) ) ) { }

			bool				Update( void );
			void				Draw( void ) { }
			void				Shutdown( void ) { }

		private:
			v8::Local<v8::Object>
								instance;
			v8::Handle<v8::Function>
								updateFunction;
		};
	}
}

#endif//_SCRIPT_H_