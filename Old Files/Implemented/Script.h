#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include <string>
#include <v8.h>

#include "Ingredient.h"

using namespace v8;
using namespace std;

namespace Graphos
{
	namespace Content
	{
		class Script : public Ingredient
		{
		public:
								Script( Local<Object> instance, GameObject* owner = nullptr ) : instance( instance ), Ingredient( owner ), updateFunction( Handle<Function>::Cast( instance->Get( String::New( "Update" ) ) ) ) { }

			bool				Update( float deltaTime );
			void				Draw( void ) { }
			void				Shutdown( void ) { }

		private:
			Local<Object>		instance;
			Handle<Function>	updateFunction;
		};
	}
}

#endif//_SCRIPT_H_