#include "Game.h"
#include "Input.h"
#include "TimeController.h"
#include "ShaderController.h"
#include "WindowController.h"
#include "Matrix4.h"

using namespace Project192;
using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Graphics;
using namespace Graphos::Utility;

void Game::Initialize( void )
{
	objects.LoadObjects( "" );
	CurrentState = GameState::Game;
	
}

bool Game::Update( void )
{
	switch( CurrentState )
	{
	case GameState::Menu:
		{
			ui->Update();

			//switch to game with F2
            if( Input::IsKeyDown( VK_F2 ) )
                    CurrentState = GameState::Game;

			break;
		}
	case GameState::Game:
		{
			objects.CallFunction( &GameObject::Update );

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

	return true;
}

void Game::Draw( void )
{
	switch( CurrentState )
	{
	case GameState::Menu:
		{
			ui->Draw();

			break;
		}
	case GameState::Game:
		{
			ShaderController::GetShader( "texture" )->SetViewMatrix( camera->GetViewMatrix() );
			ShaderController::GetShader( "texture" )->SetProjectionMatrix( WindowController::Get()->PerspectiveMatrix() );
			ShaderController::GetShader( "light" )->SetViewMatrix( camera->GetViewMatrix() );
			ShaderController::GetShader( "light" )->SetProjectionMatrix( WindowController::Get()->PerspectiveMatrix() );

			//camera->Draw();
			objects.CallFunction( &GameObject::Draw );

			break;
		}
	}
}

void Game::Shutdown( void )
{
	objects.ClearObjects();
}