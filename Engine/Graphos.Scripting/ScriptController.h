#ifndef __SCRIPT_CONTROLLER
#define __SCRIPT_CONTROLLER

#include <string>
#include <v8.h>

#include "GraphosBehavior.h"
#include "GameObject.h"
#include "OutputController.h"
#include "ClassMapper.h"

namespace Graphos
{
	namespace Core
	{
		class ScriptController
		{
		public:
			void				Initialize( void );
			void				Update( void );
			void				Shutdown( void );

			static ScriptController& Get( void )
			{
				static ScriptController instance;
				return instance;
			}

			void				InitializeObjects( GameObjectCollection* objects );

			GraphosBehavior*	CreateObjectInstance( std::string className );

			template<typename T>
			GraphosBehavior*	CreateObjectInstance( std::string className, T* owner )
			{
				using namespace v8;
				using namespace cvv8;

				if( !isInitialized )
					Initialize();

				// Create a scope
				Context::Scope contextScope( context );

				// Get an instance of the class
				Handle<Function> ctor = Handle<Function>::Cast( globalObject->Get( String::New( className.c_str() ) ) );

				// Return object
				if( !ctor.IsEmpty() )
				{
					// Create basic gameobject as well as instance of new class
					auto base = Persistent<Object>::New( CastToJS( owner )->ToObject() );
					auto inst = ctor->CallAsConstructor( 0, nullptr )->ToObject();

					if( inst.IsEmpty() )
					{
						OutputController::PrintMessage( OutputType::Error, "THE SHIT DUDE. YOU'RE OBJECT'S (of type " + className + ") EMPTY." );
						return nullptr;
					}

					for( unsigned int ii = 0; ii < inst->GetPropertyNames()->Length(); ++ii )
					{
						auto name = inst->GetPropertyNames()->Get( ii );
						if( !base->Has( name->ToString() ) )
							base->Set( name, inst->Get( name ) );
					}

					GraphosBehavior* behavior;

					// Return new script
					if( typeid( T ).hash_code() == typeid( GameObject ).hash_code() )
						behavior = new GraphosBehavior( base, reinterpret_cast<GameObject*>( owner ) );
					else
						behavior = new GraphosBehavior( base );

					behaviors.push_back( behavior );

					return behavior;
						
				}
				else
				{
					OutputController::PrintMessage( OutputType::Error, "Invalid Class Name." );
					return nullptr;
				}
			}
		
		private:
			v8::HandleScope		handleScope;
			v8::Persistent<v8::Context>
								context;
			v8::Local<v8::Object>
								globalObject;

			std::vector<GraphosBehavior*>
								behaviors;

			bool				isInitialized;
			bool				messagesWaiting;

								ScriptController( void ) : isInitialized( false ), handleScope() { }
								ScriptController( const ScriptController& );
			void				operator=( const ScriptController& );

			static void			DebugHandler( void ) { ScriptController::Get().messagesWaiting = true; }
		};
	}
}

#endif//__SCRIPT_CONTROLLER