#include "ScriptedGraphosGame.h"
#include "ScriptController.h"
#include "Input.h"
#include "WindowController.h"

using namespace Graphos::Core;
using namespace Graphos::Scripting;

void ScriptedGraphosGame::Initialize( void )
{
	CurrentState = GameState::Game;
	script = ScriptController::CreateObjectInstance<GraphosGame>( "MyGame", this );
	script->CallFunction( "Initialize" );
}

void ScriptedGraphosGame::Update( void )
{
	script->CallFunction( "Update" );

	if( CurrentState == GameState::Menu )
		ui->Update();
}

void ScriptedGraphosGame::Draw( void )
{
	script->CallFunction( "Draw" );
	
	if( CurrentState == GameState::Menu )
		ui->Draw();

	ScriptController::GetThread()->WaitFor();
}

void ScriptedGraphosGame::Shutdown( void )
{
	script->CallFunction( "Shutdown" );

	ScriptController::GetThread()->WaitFor();

	delete script;
}
