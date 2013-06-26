#ifndef __SCRIPT_CONTROLLER
#define __SCRIPT_CONTROLLER

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
			//************************************
			// Method:    Initialize
			// FullName:  Graphos::Core::ScriptController::Initialize
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: void
			//************************************
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
								ScriptController( void ) : isInitialized( false ), isolate( v8::Isolate::GetCurrent() ), handleScope( v8::Isolate::GetCurrent() ) { }
								ScriptController( const ScriptController& );
			void				operator=( const ScriptController& );

			v8::HandleScope		handleScope;
			v8::Local<v8::Context>
								context;
			v8::Local<v8::Object>
								globalObject;
			v8::Isolate*		isolate;

			bool				isInitialized;
		};
	}
}

#endif//__SCRIPT_CONTROLLER