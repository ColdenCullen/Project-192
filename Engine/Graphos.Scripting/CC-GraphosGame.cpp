#include <cvv8/XTo.hpp>
#include <cvv8/properties.hpp>
#include "ClassMapper.h"
#include "GraphosGame.h"

using namespace v8;
using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Graphics;

namespace cvv8
{
	CVV8_TypeName_IMPL((GraphosGame), "GraphosGame");
}

void cvv8::ClassCreator_SetupBindings<GraphosGame>::Initialize( Handle<v8::Object> const & target )
{
	ClassCreator<GraphosGame>& graphosGamecc( ClassCreator<GraphosGame>::Instance() );
	if( graphosGamecc.IsSealed() )
	{
		graphosGamecc.AddClassTo( TypeName<GraphosGame>::Value, target );
		return;
	}

	graphosGamecc
		( "destroy", ClassCreator<GraphosGame>::DestroyObjectCallback )
		( "Reset", MethodToInCa<GraphosGame, void( void ), &GraphosGame::Reset>::Call )
		( "Exit", MethodToInCa<GraphosGame, void( void ), &GraphosGame::Exit>::Call )
		;

	AccessorAdder graphosGameacc( graphosGamecc.Prototype() );
	graphosGameacc
		( "CurrentState",
			MemberToAccessors<GraphosGame, GameState, &GraphosGame::CurrentState>::Get,
			MemberToAccessors<GraphosGame, GameState, &GraphosGame::CurrentState>::Set )
		( "Camera",
			VarToAccessors<Camera*, &GraphosGame::camera>::Get,
			VarToAccessors<Camera*, &GraphosGame::camera>::Set )
	;

	graphosGamecc.AddClassTo( TypeName<GraphosGame>::Value, target );
};
