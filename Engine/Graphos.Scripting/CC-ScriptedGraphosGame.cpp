#include <cvv8/XTo.hpp>
#include <cvv8/properties.hpp>
#include "ClassMapper.h"
#include "ScriptedGraphosGame.h"

using namespace v8;
using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Graphics;

namespace cvv8
{
	CVV8_TypeName_IMPL((ScriptedGraphosGame), "ScriptedGraphosGame");
}

void cvv8::ClassCreator_SetupBindings<ScriptedGraphosGame>::Initialize( Handle<v8::Object> const & target )
{
	ClassCreator<ScriptedGraphosGame>& graphosGamecc( ClassCreator<ScriptedGraphosGame>::Instance() );
	if( graphosGamecc.IsSealed() )
	{
		graphosGamecc.AddClassTo( TypeName<ScriptedGraphosGame>::Value, target );
		return;
	}

	graphosGamecc
		( "destroy", ClassCreator<ScriptedGraphosGame>::DestroyObjectCallback )
		//( "Update", MethodToInCa<GameObject, void (void), &GameObject::Update>::Call )
		//( "Draw", MethodToInCa<GameObject, void (void), &GameObject::Draw>::Call )
		;

	AccessorAdder graphosGameacc( graphosGamecc.Prototype() );
	//graphosGameacc
	//	( "Objects",
	//		MemberToAccessors<ScriptedGraphosGame, GameObjectCollection, &ScriptedGraphosGame::objects>::Get,
	//		ThrowingSetter::Set )
	//	;

	// Set static methods
	Handle<Function> ctor( graphosGamecc.CtorFunction() );
	//ctor->Set( String::New( "TripleProduct" ), FunctionTemplate::New( FunctionToInCa<Vector3 (const Vector3&, const Vector3&, const Vector3&), &Vector3::TripleProduct>::Call )->GetFunction() );

	graphosGamecc.AddClassTo( TypeName<ScriptedGraphosGame>::Value, target );
};
