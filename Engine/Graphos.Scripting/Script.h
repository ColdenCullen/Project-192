#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include <v8.h>
#include <string>

#include "IComponent.h"

namespace Graphos
{
	namespace Core
	{
		class Script : public IComponent
		{
		public:
								Script( v8::Persistent<v8::Object> instance, GameObject* owner = nullptr );
								~Script( void );

			void				Update( void );
			void				Draw( void ) { }
			void				Shutdown( void ) { }

			void				CallFunction( std::string name, ... );

		private:
			v8::Persistent<v8::Object>
								instance;
			v8::Handle<v8::Function>
								updateFunction;
		};
	}
}

#endif//_SCRIPT_H_