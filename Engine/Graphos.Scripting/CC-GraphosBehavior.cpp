#include <cvv8/XTo.hpp>
#include <cvv8/properties.hpp>
#include "ClassMapper.h"
#include "GraphosBehavior.h"

using namespace v8;
using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Graphics;

NAME_CLASS(GraphosBehavior)

void cvv8::ClassCreator_SetupBindings<GraphosBehavior>::Initialize( Handle<v8::Object> const & target )
{
	ClassCreator<GraphosBehavior>& gameObjectcc( ClassCreator<GraphosBehavior>::Instance() );
	if( gameObjectcc.IsSealed() )
	{
		gameObjectcc.AddClassTo( TypeName<GraphosBehavior>::Value, target );
		return;
	}

	gameObjectcc
		( "destroy", ClassCreator<GraphosBehavior>::DestroyObjectCallback )
		( "Initialize", MethodToInCa<GraphosBehavior, void (void), &GraphosBehavior::Initialize>::Call )
		( "Update", MethodToInCa<GraphosBehavior, void (void), &GraphosBehavior::Update>::Call )
		( "Draw", MethodToInCa<GraphosBehavior, void (void), &GraphosBehavior::Draw>::Call )
		( "Shutdown", MethodToInCa<GraphosBehavior, void (void), &GraphosBehavior::Shutdown>::Call )
		;

	AccessorAdder gameObjectacc( gameObjectcc.Prototype() );
	gameObjectacc
		( "Owner",
			ConstMethodToGetter<const IComponent, GameObject* const( void ), &IComponent::Owner>::Get,
			ThrowingSetter::Set )
		;

	gameObjectcc.AddClassTo( TypeName<GraphosBehavior>::Value, target );
};