#include "Game.h"
#include "Input.h"

using namespace Project192;
using namespace Graphos::Core;

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

	if( Input::Get().IsKeyDown( VK_ESCAPE ) )
		Exit();

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
			objects.CallFunction( &GameObject::Draw );

			break;
		}
	}
}

void Game::Shutdown( void )
{
	objects.ClearObjects();
}