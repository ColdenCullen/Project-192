#ifndef _SCRIPTCONTROLLER_H_
#define _SCRIPTCONTROLLER_H_

#include <string>
#include <v8.h>

#include "Script.h"
#include "GameObject.h"

using namespace v8;
using namespace std;
using namespace Graphos;

namespace Graphos
{
	namespace Content
	{
		class ScriptController
		{
		public:
			bool				Initialize( void );
			void				Shutdown( void );

			Script*				CreateObjectInstance( string className, unsigned int ownerID, GameObject* owner = nullptr );

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

			HandleScope			handleScope;
			Persistent<Context>	context;
			Local<Object>		globalObject;

			bool				isInitialized;
		};
	}
}

#endif//_SCRIPTCONTROLLER_H_