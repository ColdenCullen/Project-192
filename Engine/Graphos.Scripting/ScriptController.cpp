// Class Creators
#include <cvv8\ClassCreator.hpp>

#include <iostream>
#include <v8-debug.h>

#include "OutputController.h"
#include "ScriptController.h"
#include "Input.h"
#include "Config.h"
#include "File.h"
#include "ThreadController.h"

using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Utility;
using namespace Graphos::Graphics;
using namespace Graphos::Scripting;
using namespace v8;
using namespace cvv8;

Thread* ScriptController::thisThread = nullptr;
Isolate* ScriptController::isolate = nullptr;

#pragma region Handlers
Handle<Value> IsKeyDown( const Arguments& args )
{
	return Boolean::New( Input::IsKeyDown( args[ 0 ]->Int32Value() ) );
}

Handle<Value> PrintHandler( const Arguments& args )
{
	string message = "";

	for( int ii = 0; ii < args.Length(); ++ii )
		message += string( *String::Utf8Value( args[ ii ] ) );

	OutputController::PrintMessage( OutputType::Info, message );

	return Undefined();
}
#pragma endregion

void ScriptController::Initialize( void )
{
	thisThread->Invoke( [&]()
	{
		// Create global object template, add function handlers
		Handle<ObjectTemplate> globalObjectTemplate = ObjectTemplate::New();
		//globalObjectTemplate->Set( "include", FunctionTemplate::New( FunctionCallback( IncludeHandler ) ) );
		globalObjectTemplate->Set( "log", FunctionTemplate::New( PrintHandler ) );

		// Setup Input
		Handle<ObjectTemplate> input = ObjectTemplate::New();
		input->Set( "IsKeyDown", FunctionTemplate::New( IsKeyDown ) );
		globalObjectTemplate->Set( "Input", input );

		// Create the context for initializing the scripts
		context = Context::New( /*isolate,*/ nullptr, globalObjectTemplate );

		// Scope for created variables
		Context::Scope contextScope( context );

#ifdef _DEBUG
		v8::Debug::EnableAgent( "Graphos", 5858, false );
#endif

		auto file = File( Config::GetData<string>( "Scripts.Path" ) );

		// Compile
		auto compiled = v8::Script::Compile(
			String::New( file.GetContents().c_str() ),
			String::New( file.GetFileName().c_str() )
			);

		if( compiled.IsEmpty() )
			throw exception( "Error compiling JS." );

		// Run!
		compiled->Run();

		// Get the "global" object
		globalObject = context->Global();

		// Bind types
		ClassMapper::BindGraphosTypes( globalObject );
	}, true );
}

GraphosBehavior* ScriptController::CreateObjectInstance( std::string className )
{
	using namespace v8;
	using namespace cvv8;

	GraphosBehavior* behavior = nullptr;

	thisThread->Invoke( [&, className]()
	{
		// Create a scope
		Context::Scope contextScope( context );

		// Get an instance of the class
		Handle<Function> ctor = Handle<Function>::Cast( globalObject->Get( String::New( className.c_str() ) ) );

		// Return object
		if( !ctor.IsEmpty() )
		{
			// Create basic gameobject as well as instance of new class
			behavior = new Graphos::Core::GraphosBehavior(
				Persistent<Object>::New(
				ctor->CallAsConstructor( 0, nullptr )->ToObject()
				)
				);
		}
	}, true);

	return behavior;
}

void ScriptController::SetThread( Thread* thread )
{
	if( !thisThread )
		thisThread = thread;
}


void ScriptController::Shutdown( void )
{
/*
	context->Dispose();

	isInitialized = false;
*/
}

void ScriptController::InitializeObjects( GameObjectCollection* objects )
{
	for( auto obj : behaviors )
		obj->Initialize( objects );
}
