#include <iostream>

#include "ScriptController.h"
#include "Input.h"
#include "Config.h"

#define _USE_READ_FILE
#include "Helpers.h"

using namespace std;
using namespace Graphos::Content;
using namespace Graphos::Graphics;

#pragma region Handlers
#pragma region Helpers
Handle<Value> IsKeyDown( const Arguments& args )
{
	return Boolean::New( Input::Get().IsKeyDown( args[ 0 ]->Int32Value() ) );
}

Handle<Value> IncludeHandler(const Arguments& args)
{
	for (int i = 0; i < args.Length(); i++)
	{
		String::Utf8Value str(args[i]);

		// load_file loads the file with this name into a string,
		// I imagine you can write a function to do this :)
		std::string js_file = Helpers::ReadFile(*str);

		if(js_file.length() > 0)
		{
			Handle<String> source = String::New( js_file.c_str() );
			Handle<v8::Script> script = v8::Script::Compile( source );
			return script->Run();
		}
	}
	return Undefined();
}

Handle<Value> PrintHandler( const Arguments& args )
{
	for( int ii = 0; ii < args.Length(); ++ii )
		cout << *String::Utf8Value( args[ ii ] );

	cout << endl;

	return Undefined();
}
#pragma endregion

#pragma region Transform
// Access transform
Handle<Value> GetTransform(Local<String> property, const AccessorInfo& info)
{
	// Get object holder
	Local<Object> self = info.Holder();

	Handle<Object> global = info.GetIsolate()->GetCurrentContext()->Global();

	// Get owner
	GameObject* owner = GameObject::GetGameObject( self->Get( String::New( "id" ) )->Uint32Value() );

	// Create position
	Handle<Object> position = Handle<Function>::Cast( global->Get( String::New( "Vector3" ) ) )->CallAsConstructor( 0, nullptr )->ToObject();
	position->Set( String::New( "x" ), Number::New( owner->transform.Position().x ) );
	position->Set( String::New( "y" ), Number::New( owner->transform.Position().y ) );
	position->Set( String::New( "z" ), Number::New( owner->transform.Position().z ) );

	// Create rotation
	Handle<Object> rotation = Handle<Function>::Cast( global->Get( String::New( "Vector3" ) ) )->CallAsConstructor( 0, nullptr )->ToObject();
	rotation->Set( String::New( "x" ), Number::New( owner->transform.Rotation().x ) );
	rotation->Set( String::New( "y" ), Number::New( owner->transform.Rotation().y ) );
	rotation->Set( String::New( "z" ), Number::New( owner->transform.Rotation().z ) );

	// Create scale
	Handle<Object> scale = Handle<Function>::Cast( global->Get( String::New( "Vector3" ) ) )->CallAsConstructor( 0, nullptr )->ToObject();
	scale->Set( String::New( "x" ), Number::New( owner->transform.Scale().x ) );
	scale->Set( String::New( "y" ), Number::New( owner->transform.Scale().y ) );
	scale->Set( String::New( "z" ), Number::New( owner->transform.Scale().z ) );

	// Link them all
	Handle<Object> transform = Object::New();
	transform->Set( String::New( "position" ), position );
	transform->Set( String::New( "rotation" ), rotation );
	transform->Set( String::New( "scale" ), scale );

	return transform;
}

/*
// Change transform
void SetTransform(Local<String> property, Local<Value> value, const AccessorInfo& info)
{
	Local<Object> self = info.Holder();
	Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
	void* ptr = wrap->Value();
	static_cast<Point*>(ptr)->x_ = value->Int32Value();
}
*/
#pragma endregion
#pragma endregion

bool ScriptController::Initialize( void )
{
	// Create global object template, add function handlers
	Handle<ObjectTemplate> globalObjectTemplate = ObjectTemplate::New();
	globalObjectTemplate->Set( "include", FunctionTemplate::New( IncludeHandler ) );
	globalObjectTemplate->Set( "log", FunctionTemplate::New( PrintHandler ) );

	// Setup Input
	Handle<ObjectTemplate> input = ObjectTemplate::New();
	input->Set( "IsKeyDown", FunctionTemplate::New( IsKeyDown ) );
	globalObjectTemplate->Set( "Input", input );

	// Create the context for initializing the scripts
	context = Context::New( nullptr, globalObjectTemplate );

	// Scope for created variables
	Context::Scope contextScope( context );

	// Load and compile script
	v8::Script::Compile(
		String::New(
			Helpers::ReadFile(
				Config::Get().GetData<string>( "scripts.mainPath" )
			).c_str()
		)
	)->Run();

	// Get the "global" object
	globalObject = context->Global();

	return true;
}

void ScriptController::Shutdown( void )
{
	if( isInitialized )
	{
		//handleScope.~HandleScope();
		//context.Dispose();

		isInitialized = false;
	}
}

Content::Script* ScriptController::CreateObjectInstance( string className, unsigned int ownerID, GameObject* owner /*= nullptr */ )
{
	if( !isInitialized )
		Initialize();

	// Create a scope
	Context::Scope contextScope( context );

	// Get an instance of the class
	Local<Function> ctor = Local<Function>::Cast( globalObject->Get( String::New( className.c_str() ) ) );

	// Return object
	if( !ctor.IsEmpty() )
	{
		// Get object
		Local<Object> instance = ctor->CallAsConstructor( 0, nullptr )->ToObject();

		// Set id
		instance->Set( String::New( "id" ), Int32::New( ownerID ) );

		// Set transform accessor
		instance->SetAccessor( String::New( "transform" ), GetTransform, nullptr );

		// Return new script
		return new Script( instance, owner );
	}
	else
		return nullptr;
}

/*
void ScriptController::MyHandler::OnMethodCall( WebView* caller, unsigned int remoteObjId, const WebString& methodName, const JSArray& args )
{
	if( methodName == WSLit( "log" ) )
	{
		if( args.size() )
		{
			cout << args[ 0 ].ToString();
	
			for( unsigned int ii = 1; ii < args.size(); ++ii )
				cout << ", " << args[ ii ].ToString();
		}

		cout << endl;
	}
}

JSValue ScriptController::MyHandler::OnMethodCallWithReturnValue( WebView* caller, unsigned int remoteObjectId, const WebString& methodName, const JSArray& args )
{
	if( remoteObjectId == owner->input.remote_id() && methodName == WSLit( "IsKeyDown" ) && args.size() )
	{
		if( args[ 0 ].IsInteger() )
			return JSValue( Input::Get().IsKeyDown( args[ 0 ].ToInteger() ) );
	}
	if( methodName == WSLit( "UpdateTransformC" ) && args.size() == 1 )
	{
		// Get GameObject reference
		string name = ToString( args[ 0 ].ToString() );

		GameObject& obj = GameObject::GetGameObject( name );

		// Get values
		const Vector3& positionVec = obj.transform.Position();

		JSObject transform, position;
		position.SetProperty( WSLit( "x" ), JSValue( positionVec.x ) );
		position.SetProperty( WSLit( "y" ), JSValue( positionVec.y ) );
		position.SetProperty( WSLit( "z" ), JSValue( positionVec.z ) );

		transform.SetProperty( WSLit( "position" ), position );

		return transform;
	}

	return JSValue::Undefined();
}
*/