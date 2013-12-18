#include <cvv8/XTo.hpp>
#include <cvv8/properties.hpp>
#include "ClassMapper.h"
#include "GameObject.h"
#include "Vector3.h"

using namespace v8;
using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Graphics;

NAME_CLASS(GameObject)

void cvv8::ClassCreator_SetupBindings<GameObject>::Initialize( Handle<v8::Object> const & target )
{
	ClassCreator<GameObject>& gameObjectcc( ClassCreator<GameObject>::Instance() );
	if( gameObjectcc.IsSealed() )
	{
		gameObjectcc.AddClassTo( TypeName<GameObject>::Value, target );
		return;
	}

	gameObjectcc
		( "destroy", ClassCreator<GameObject>::DestroyObjectCallback )
		( "Update", MethodToInCa<GameObject, void (void), &GameObject::Update>::Call )
		( "Draw", MethodToInCa<GameObject, void (void), &GameObject::Draw>::Call )
		( "MakeShootyBall", MethodToInCa<GameObject, void (Vector3*), &GameObject::MakeShootyBall>::Call )
		;

	AccessorAdder gameObjectacc( gameObjectcc.Prototype() );
	gameObjectacc
		( "Transform",
			MemberToAccessors<GameObject, Transform*, &GameObject::transform>::Get,
			ThrowingSetter::Set )
		;

	gameObjectcc.AddClassTo( TypeName<GameObject>::Value, target );
};
