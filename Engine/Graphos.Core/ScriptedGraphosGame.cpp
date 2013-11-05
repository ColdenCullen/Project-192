#include "ScriptedGraphosGame.h"

using namespace Graphos::Core;
using namespace Graphos::Scripting;

void ScriptedGraphosGame::Initialize( void )
{
	script = ScriptController::Get().CreateObjectInstance( "GraphosGame", this );
	script->CallFunction( "Initialize" );
}

void ScriptedGraphosGame::Update( void )
{
	script->CallFunction( "Update" );
}

void ScriptedGraphosGame::Draw( void )
{
	script->CallFunction( "Draw" );
}

void ScriptedGraphosGame::Shutdown( void )
{
	script->CallFunction( "Shutdown" );

	delete script;

	system( "pause" );
}
