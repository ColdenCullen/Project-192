#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include <v8.h>
#include <string>

#include "IComponent.h"
#include "JsonObject.h"

namespace Graphos
{
	namespace Core
	{
		class GameObjectCollection;

		class GraphosBehavior : public IComponent
		{
		public:
								GraphosBehavior( v8::Persistent<v8::Object> instance, GameObject* owner = nullptr );
								~GraphosBehavior( void );

			void				SetInitialValues( Utility::JsonObject initVals );

			void				Initialize( GameObjectCollection* objects );
			void				Update( void );
			void				Draw( void ) { }
			void				Shutdown( void ) { }

			void				CallFunction( std::string name, ... );

		private:
			v8::Persistent<v8::Object>
								instance;
			v8::Handle<v8::Function>
								updateFunction;

			Utility::JsonObject	initialValues;
		};
	}
}

#endif//_SCRIPT_H_