#ifndef __SCRIPT_CONTROLLER
#define __SCRIPT_CONTROLLER

#include <string>
#include <v8\v8.h>

#include "Script.h"
#include "GameObject.h"

namespace Graphos
{
	namespace Core
	{
		class ScriptController
		{
		public:
			void				Initialize( void );
			void				Shutdown( void );

			Script*				CreateObjectInstance( std::string className, GameObject* owner = nullptr );

			static ScriptController& Get( void )
			{
				static ScriptController instance;
				return instance;
			}
		
		private:
								ScriptController( void ) : isInitialized( false ), handleScope() { }
								ScriptController( const ScriptController& );
			void				operator=( const ScriptController& );

			v8::HandleScope		handleScope;
			v8::Persistent<v8::Context>
								context;
			v8::Local<v8::Object>
								globalObject;

			bool				isInitialized;
		};
	}
}

#endif//__SCRIPT_CONTROLLER