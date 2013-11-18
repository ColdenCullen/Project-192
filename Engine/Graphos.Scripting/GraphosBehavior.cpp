#include <iostream>
#include <cstdarg>

#include "GraphosBehavior.h"
#include "TimeController.h"
#include "OutputController.h"
#include "GameObjectCollection.h"
#include "ClassMapper.h"
#include "ThreadManager.h"

using namespace v8;
using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Utility;

GraphosBehavior::GraphosBehavior( Persistent<Object> instance, GameObject* owner /*= nullptr */ )
	: IComponent( owner ), instance( instance )
{
	updateFunction = Handle<Function>::Cast( instance->Get( String::New( "Update" ) ) );

	if( !updateFunction->IsFunction() )
		OutputController::PrintMessage( OutputType::Warning, "Invalid Update function." );
}

GraphosBehavior::~GraphosBehavior( void )
{

}

void GraphosBehavior::SetInitialValues( JsonObject initVals )
{
	initialValues = initVals;
}

void GraphosBehavior::Initialize( GameObjectCollection* objects )
{
	for( auto val : initialValues.node.getMemberNames() )
	{
		JsonObject current = initialValues.Get<JsonObject>( val );
		Handle<Value> toSet;

		if( current.node.isString() && current.Get<string>( "" ).find( "o:" ) != string::npos )
		{
			string objectName = current.Get<string>( "" ).substr( 2 );

			toSet = cvv8::CastToJS( objects->GetObjectByName( objectName ) );
		}
		else
		{
			toSet = current.Get<Handle<Value>>( "" );
		}


		instance->Set( String::New( val.c_str() ), toSet );
	}
}

void GraphosBehavior::Update( void )
{
	CallFunction( "OnUpdate" );
}

void GraphosBehavior::CallFunction( string name, ... )
{
	auto exec = [&, name]()
	{
		auto func = Handle<Function>::Cast( instance->Get( String::New( name.c_str() ) ) );

		if( !func->IsFunction() )
			OutputController::PrintMessage( OutputType::Error, "Invalid " + name + " function." );

		int count = 0;
		Handle<Value>* vals = NULL;
		/*
		va_list args;
		va_start( args, count );
	
		if( count )
		{
			vals = new Handle<Value>[ count ];
			for( int ii = 0; ii < count; ++ii )
				vals[ ii ] = va_arg( args, Handle<Value> );
		}
		va_end( args );
		*/

		func->Call( instance, count, vals );
	};

	if( ThreadManager::OnMainThread() )
	{
		exec();
	}
	else
	{
		ThreadManager::Invoke( exec );
	}
}
