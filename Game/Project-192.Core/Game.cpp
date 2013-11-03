#include "Game.h"
#include "Input.h"
#include "TimeController.h"
#include "ShaderController.h"
#include "WindowController.h"
#include "Matrix4.h"
#include "PhysicsController.h"

using namespace Project192;
using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Physics;
using namespace Graphos::Graphics;

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

			break;
		}
	case GameState::Game:
		{
			objects.CallFunction( &GameObject::Update );

			break;
		}
	}

	if( Input::IsKeyDown( VK_ESCAPE ) )
		Exit();

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