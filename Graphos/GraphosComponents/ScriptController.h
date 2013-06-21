#ifndef _SCRIPTCONTROLLER_H_
#define _SCRIPTCONTROLLER_H_

#include <string>
#include <v8.h>

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

			Script*				CreateObjectInstance( std::string className, unsigned int ownerID, GameObject* owner = nullptr );

			static
			ScriptController&	Get( void )
			{
				static ScriptController instance;
				return instance;
			}
		
		private:
								ScriptController( void ) : isInitialized( false ) { }
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

#endif//_SCRIPTCONTROLLER_H_