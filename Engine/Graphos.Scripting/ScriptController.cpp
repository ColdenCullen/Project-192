#include <iostream>
#include <cvv8/ClassCreator.hpp>
#include <v8/v8-debug.h>

#include "ScriptController.h"
#include "Input.h"
#include "Config.h"
#include "File.h"
#include "ClassMapper.h"

// Class Creators
#include "CC-GameObject.h"

using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Graphics;
using namespace Graphos::Scripting;
using namespace v8;
using namespace cvv8;

#pragma region Handlers
Handle<Value> IsKeyDown( const Arguments& args )
{
	return Boolean::New( ISingleton<Input>::Get().IsKeyDown( args[ 0 ]->Int32Value() ) );
}

Handle<Value> PrintHandler( const Arguments& args )
{
	for( int ii = 0; ii < args.Length(); ++ii )
		cout << *String::Utf8Value( args[ ii ] );

	cout << endl;

	return Undefined();
}
#pragma endregion

void ScriptController::Initialize( void )
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

	// Compile
	auto compiled = v8::Script::Compile(
		String::New( 
				File::ReadFile( ISingleton<Config>::Get().GetData<string>( "Scripts.Path" ) ).c_str()
			)
		);

	if( compiled.IsEmpty() )
		throw exception( "Error compiling JS." );

	// Run!
	compiled->Run();

	// Get the "global" object
	globalObject = context->Global();

	// Bind types
	ClassMapper::BindGraphosTypes( globalObject );

	isInitialized = true;
}

void ScriptController::Shutdown( void )
{
	if( isInitialized )
	{
		//context->Dispose();

		//isInitialized = false;
	}
}

Graphos::Core::Script* ScriptController::CreateObjectInstance( string className, GameObject* owner /*= nullptr*/ )
{
	if( !isInitialized )
		Initialize();

	// Create a scope
	Context::Scope contextScope( context );

	// Get an instance of the class
	Handle<Function> ctor = Handle<Function>::Cast( globalObject->Get( String::New( className.c_str() ) ) );

	// Return object
	if( !ctor.IsEmpty() )
	{
		auto gameObject = CastToJS( *owner )->ToObject();
		gameObject->SetPointerInInternalField( ClassCreator_InternalFields<GameObject>::NativeIndex, owner );
		auto inst = ctor->CallAsConstructor( 0, nullptr )->ToObject();

		for( int ii = 0; ii < inst->GetPropertyNames()->Length(); ++ii )
		{
			auto name = inst->GetPropertyNames()->Get( ii );
			if( !gameObject->Has( name->ToString() ) )
				gameObject->Set( name, inst->Get( name ) );
		}

		// Return new script
 		return new Graphos::Core::Script( gameObject, owner );
	}
	else
	{
		throw exception( "Invalid Class Name." );
	}
}