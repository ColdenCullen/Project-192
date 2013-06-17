#include "Game.h"

using namespace Project192;
using namespace Graphos::Core;

Game::Game( void )
{

}

Game::~Game( void )
{

}

void Game::Initialize( void )
{
	objects.LoadObjects( "" );
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