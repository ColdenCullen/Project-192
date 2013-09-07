#include "Game.h"
#include "Input.h"
#include "Time.h"
#include "ShaderController.h"
#include "WindowController.h"
#include "Matrix4.h"

using namespace Project192;
using namespace Graphos::Core;
using namespace Graphos::Math;
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
			//camera->Update();

			objects.CallFunction( &GameObject::Update );

			break;
		}
	}

	if( ISingleton<Input>::Get().IsKeyDown( VK_ESCAPE ) )
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
			ISingleton<ShaderController>::Get().GetShader( "texture" ).SetUniform( "cameraMatrix", /*camera->transform.WorldMatrix()*/Matrix4::Identity );
			ISingleton<ShaderController>::Get().GetShader( "texture" ).SetUniform( "projectionMatrix", WindowController::Get().PerspectiveMatrix() );

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