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

void Game::Initialize( void )
{
	objects.LoadObjects( "" );
	cube = objects.GetObjectByName( "Cube" );
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

			//float rotation = 5.0f * ISingleton<Time>::Get().GetDeltaTime();
			//cube->transform.Rotate( rotation, rotation, 0.0f );

			break;
		}
	}

	if( ISingleton<Input>::Get().IsKeyDown( VK_ESCAPE ) )
		Exit();

	if( ISingleton<Input>::Get().IsKeyDown( VK_F5 ) )
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
			ISingleton<ShaderController>::Get().GetShader( "light" )->SetViewMatrix( Matrix4::Identity );
			ISingleton<ShaderController>::Get().GetShader( "light" )->SetProjectionMatrix( WindowController::Get().PerspectiveMatrix() );
			ISingleton<ShaderController>::Get().GetShader( "simple" )->SetViewMatrix( Matrix4::Identity );
			ISingleton<ShaderController>::Get().GetShader( "simple" )->SetProjectionMatrix( WindowController::Get().PerspectiveMatrix() );

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