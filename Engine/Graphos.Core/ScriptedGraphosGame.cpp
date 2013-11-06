#include "ScriptedGraphosGame.h"
#include "ScriptController.h"
#include "Input.h"
#include "WindowController.h"

using namespace Graphos::Core;
using namespace Graphos::Scripting;

void ScriptedGraphosGame::Initialize( void )
{
	CurrentState = GameState::Game;
	script = ScriptController::Get().CreateObjectInstance<GraphosGame>( "MyGame", this );
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
	ShaderController::GetShader( "texture" )->SetViewMatrix( camera->GetViewMatrix() );
	//ShaderController::GetShader( "texture" )->SetProjectionMatrix( WindowController::Get()->PerspectiveMatrix() );
	ShaderController::GetShader( "light" )->SetViewMatrix( camera->GetViewMatrix() );
	//ShaderController::GetShader( "light" )->SetProjectionMatrix( WindowController::Get()->PerspectiveMatrix() );

	script->CallFunction( "Draw" );
	
	if( CurrentState == GameState::Menu )
		ui->Draw();
}

void ScriptedGraphosGame::Shutdown( void )
{
	script->CallFunction( "Shutdown" );

	objects.ClearObjects();

	delete script;
}
