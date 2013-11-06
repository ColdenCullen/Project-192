#ifndef __SCRIPT_CONTROLLER
#define __SCRIPT_CONTROLLER

#include <string>
#include <v8\v8.h>
#include <cvv8\ClassCreator.hpp>

#include "Script.h"
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
			void				Shutdown( void );

			static ScriptController& Get( void )
			{
				static ScriptController instance;
				return instance;
			}

			template<typename T>
			Graphos::Core::Script* CreateObjectInstance( std::string className, T* owner )
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
					/*
					// Create basic gameobject as well as instance of new class
					auto base = Persistent<Object>::New( CastToJS( owner )->ToObject() );
					auto inst = ctor->CallAsConstructor( 0, nullptr )->ToObject();

					for( unsigned int ii = 0; ii < inst->GetPropertyNames()->Length(); ++ii )
					{
						auto name = inst->GetPropertyNames()->Get( ii );
						if( !base->Has( name->ToString() ) )
							base->Set( name, inst->Get( name ) );
					}
					*/

					auto base = Persistent<Object>::New( ctor->CallAsConstructor( 0, nullptr )->ToObject() );
					base->Set( String::New( "Owner" ), CastToJS( owner ) );

					// Return new script
					if( typeid( T ).hash_code() == typeid( GameObject ).hash_code() )
						return new Graphos::Core::Script( base, reinterpret_cast<GameObject*>( owner ) );
					else
						return new Graphos::Core::Script( base );
				}
				else
				{
					OutputController::PrintMessage( OutputType::Error, "Invalid Class Name." );
					return nullptr;
				}
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