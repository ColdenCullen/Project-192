#include <vector>
#include <string>
#include <cstdlib>

#include "GraphosGame.h"
#include "File.h"
#include "GraphicsController.h"
#include "AdapterController.h"
#include "ShaderController.h"
#include "AssetController.h"
#include "ScriptController.h"
#include "Input.h"
#include "TimeController.h"
#include "Config.h"
#include "OutputController.h"
#include "PhysicsController.h"
#include "JsonController.h"
#include "TaskManager.h"

using namespace Graphos::Core;
using namespace Graphos::Physics;
using namespace Graphos::Graphics;
using namespace Graphos::Utility;

void GraphosGame::Run( void )
{
	//////////////////////////////////////////////////////////////////////////
	// Initialize
	//////////////////////////////////////////////////////////////////////////

	// Initialize values and controllers
	quit = false;

	// Init time
	Time::Initialize();
	TaskManager::Initialize();

	Start();

	// Loop until there is a quit message from the window or the user.
	while( !quit )
	{
		//try
		{
			if( CurrentState == GameState::Reseting )
				Reset();

			//////////////////////////////////////////////////////////////////////////
			// Update
			//////////////////////////////////////////////////////////////////////////

			// Platform specific program stuff
			GraphicsController::MessageLoop();

			// Update time
			Time::Update();

			// Update input
			InputController::Update();

			// Update physics
			if( CurrentState == GameState::Game )
				PhysicsController::StepPhysics( Time::GetDeltaTime() );

			// Do the updating of the child class.
			Update();

			//////////////////////////////////////////////////////////////////////////
			// Draw
			//////////////////////////////////////////////////////////////////////////

			// Begin drawing
			AdapterController::Get()->BeginDraw();

			// Draw in child class
			Draw();

			// End drawing
			AdapterController::Get()->EndDraw();
		}
		/*
		catch (std::exception e)
		{
			OutputController::PrintMessage( OutputType::OT_ERROR, e.what() );
			system( "pause" );
			break;
		}
		*/
	}

	Stop();
}

void GraphosGame::Reset( void )
{
	JsonController::Initialize();
	Config::Initialize();
	GraphicsController::Reload();

	// Call child shutdown
	Shutdown();

	// Shutdown UI and controllers
	delete_s( ui );
	PhysicsController::Shutdown();
	AssetController::Shutdown();
	ScriptController::Get().Shutdown();

	// Restart
	ScriptController::Get().Initialize();
	AssetController::Initialize();
	PhysicsController::Initialize();
	ui = new UserInterface( this );

	Initialize();
}

void GraphosGame::Exit( void )
{
	quit = true;
}

void GraphosGame::Start( void )
{
	CurrentState = GameState::Menu;
	camera = nullptr;

	JsonController::Initialize();
	Config::Initialize();
	GraphicsController::Initialize();
	AssetController::Initialize();
	PhysicsController::Initialize();
	ScriptController::Get().Initialize();

	ui = new UserInterface( this );

	Initialize();
}

void GraphosGame::Stop( void )
{
	// Call child shutdown
	Shutdown();

	// Shutdown UI and controllers
	delete_s( ui );
	ShaderController::Shutdown();
	PhysicsController::Shutdown();
	AssetController::Shutdown();
	ScriptController::Get().Shutdown();
	GraphicsController::Shutdown();
}

void GraphosGame::Initialize( void )
{
	throw std::exception( "Do not create an instance of GraphosGame!" );
}

void GraphosGame::Update( void )
{
	throw std::exception( "Do not create an instance of GraphosGame!" );
}

void GraphosGame::Draw( void )
{
	throw std::exception( "Do not create an instance of GraphosGame!" );
}

void GraphosGame::Shutdown( void )
{
	throw std::exception( "Do not create an instance of GraphosGame!" );
}

Camera* GraphosGame::camera;
