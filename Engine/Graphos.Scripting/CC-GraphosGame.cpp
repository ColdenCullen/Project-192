#include <cvv8/XTo.hpp>
#include <cvv8/properties.hpp>
#include "ClassMapper.h"
#include "GraphosGame.h"

using namespace v8;
using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Graphics;

NAME_CLASS(GraphosGame)

void cvv8::ClassCreator_SetupBindings<GraphosGame>::Initialize( Handle<v8::Object> const & target )
{
	ClassCreator<GraphosGame>& gameObjectcc( ClassCreator<GraphosGame>::Instance() );
	if( gameObjectcc.IsSealed() )
	{
		gameObjectcc.AddClassTo( TypeName<GraphosGame>::Value, target );
		return;
	}

	gameObjectcc
		( "destroy", ClassCreator<GraphosGame>::DestroyObjectCallback )
		//( "Update", MethodToInCa<GameObject, void (void), &GameObject::Update>::Call )
		//( "Draw", MethodToInCa<GameObject, void (void), &GameObject::Draw>::Call )
		;

	AccessorAdder gameObjectacc( gameObjectcc.Prototype() );
	gameObjectacc
		( "Transform",
		MemberToAccessors<GraphosGame, Transform*, &GraphosGame::transform>::Get,
		ThrowingSetter::Set )
		;

	// Set static methods
	Handle<Function> ctor( gameObjectcc.CtorFunction() );
	//ctor->Set( String::New( "TripleProduct" ), FunctionTemplate::New( FunctionToInCa<Vector3 (const Vector3&, const Vector3&, const Vector3&), &Vector3::TripleProduct>::Call )->GetFunction() );

	gameObjectcc.AddClassTo( TypeName<GraphosGame>::Value, target );
};
