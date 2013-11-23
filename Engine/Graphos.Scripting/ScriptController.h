#ifndef __SCRIPT_CONTROLLER
#define __SCRIPT_CONTROLLER

#include <string>
#include <v8.h>

#include "GraphosBehavior.h"
#include "GameObject.h"
#include "OutputController.h"
#include "ClassMapper.h"
#include "GraphosThread.h"

namespace Graphos
{
	namespace Core
	{
		class ScriptController
		{
		public:
			static void			SetThread( Utility::Thread* thread );
			static Thread* const GetThread( void ) { return thisThread; }

			static void			Initialize( void );
			static void			Shutdown( void );

			static void			InitializeObjects( GameObjectCollection* objects );

#pragma region CreateObjectInstance
			static GraphosBehavior* CreateObjectInstance( std::string className );

			template<typename T>
			static GraphosBehavior* CreateObjectInstance( std::string className, T* owner )
			{
				using namespace v8;
				using namespace cvv8;

				GraphosBehavior* behavior = nullptr;

				thisThread->Invoke([&, className, owner]() -> void
				{
					HandleScope handleScope;

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
							return;
						}

						for( unsigned int ii = 0; ii < inst->GetPropertyNames()->Length(); ++ii )
						{
							auto name = inst->GetPropertyNames()->Get( ii );
							if( !base->Has( name->ToString() ) )
								base->Set( name, inst->Get( name ) );
						}

						// Return new script
						if( typeid( T ).hash_code() == typeid( GameObject ).hash_code() )
							behavior = new GraphosBehavior( base, reinterpret_cast<GameObject*>( owner ) );
						else
							behavior = new GraphosBehavior( base );

						behaviors.push_back( behavior );
					}
					else
					{
						OutputController::PrintMessage( OutputType::Error, "Invalid Class Name." );
					}
				}, true );

				return behavior;
			}
#pragma endregion
		
		private:
			// v8-y things
			static v8::Isolate*	isolate;
			static v8::Persistent<v8::Context>
								context;
			static v8::Persistent<v8::Object>
								globalObject;

			// Scripts
			static std::vector<GraphosBehavior*>
								behaviors;

			static Utility::Thread* thisThread;

								ScriptController( void ) { } //: handleScope() { }
								ScriptController( const ScriptController& );
			void				operator=( const ScriptController& );
		};
	}
}

#endif//__SCRIPT_CONTROLLER