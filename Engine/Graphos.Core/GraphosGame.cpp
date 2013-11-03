#include <vector>
#include <string>
#include <json/json.h>
#include <cstdlib>

#include "GraphosGame.h"
#include "File.h"
#include "Physics.h"
#include "GraphicsController.h"
#include "AdapterController.h"
#include "ShaderController.h"
#include "AssetController.h"
#include "ScriptController.h"
#include "Input.h"
#include "TimeController.h"
#include "Config.h"
#include "OutputController.h"

using namespace Graphos::Core;
using namespace Graphos::Physics;
using namespace Graphos::Graphics;

void GraphosGame::Run( void )
{
	//////////////////////////////////////////////////////////////////////////
	// Initialize
	//////////////////////////////////////////////////////////////////////////

	// Initialize values and controllers
	quit = false;

	Start();

	// Init time
	Time::Initialize();

	// Loop until there is a quit message from the window or the user.
	while( !quit )
	{
		try
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
			Input::Update();

			// Update physics
			Physics::Physics::Update();

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
		catch (std::exception e)
		{
			OutputController::PrintMessage( OutputType::OT_ERROR, e.what() );
			break;
		}
	}

	Stop();
}

void GraphosGame::Reset( void )
{
	Config::Initialize();
	GraphicsController::Reload();

	// Call child shutdown
	Shutdown();

	// Shutdown UI and controllers
	delete_s( ui );
	Physics::Physics::Shutdown();
	AssetController::Shutdown();
	ScriptController::Get().Shutdown();

	// Restart
	ScriptController::Get().Initialize();
	AssetController::Initialize();
	Physics::Physics::Initialize();
	Input::ui = ui = new UserInterface( this );

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

	Config::Initialize();

	GraphicsController::Initialize();

	AssetController::Initialize();

	Physics::Physics::Initialize();

	ScriptController::Get().Initialize();

	Input::ui = ui = new UserInterface( this );

	Initialize();
}

void GraphosGame::Stop( void )
{
	// Call child shutdown
	Shutdown();

	// Shutdown UI and controllers
	delete_s( ui );
	ShaderController::Shutdown();
	Physics::Physics::Shutdown();
	AssetController::Shutdown();
	ScriptController::Get().Shutdown();
	GraphicsController::Shutdown();
}

Camera* Graphos::Core::GraphosGame::camera;
