#include "ScriptedGraphosGame.h"
#include "ScriptController.h"
#include "Input.h"
#include "WindowController.h"

using namespace Graphos::Core;
using namespace Graphos::Scripting;

void ScriptedGraphosGame::Initialize( void )
{
	CurrentState = GameState::Game;
	script = ScriptController::Get().CreateObjectInstance( "MyGame", this );
	script->CallFunction( "Initialize" );
}

void ScriptedGraphosGame::Update( void )
{
	script->CallFunction( "Update" );

	switch( CurrentState )
	{
	case GameState::Menu:
		{
			//switch to game with F2
			if( Input::IsKeyDown( VK_F2 ) )
				CurrentState = GameState::Game;

			ui->Update();

			break;
		}
	case GameState::Game:
		{
			//switch to menu with F1
			if( Input::IsKeyDown( VK_F1 ) )
				CurrentState = GameState::Menu;

			break;
		}
	}

	// Quit game with Escape
	if( Input::IsKeyDown( VK_ESCAPE ) )
		Exit();

	// Reset game with F5
	if( Input::IsKeyDown( VK_F5 ) )
		Reset();
}

void ScriptedGraphosGame::Draw( void )
{
	ShaderController::GetShader( "texture" )->SetViewMatrix( camera->GetViewMatrix() );
	ShaderController::GetShader( "texture" )->SetProjectionMatrix( WindowController::Get()->PerspectiveMatrix() );
	ShaderController::GetShader( "light" )->SetViewMatrix( camera->GetViewMatrix() );
	ShaderController::GetShader( "light" )->SetProjectionMatrix( WindowController::Get()->PerspectiveMatrix() );

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
