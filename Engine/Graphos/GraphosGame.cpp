#include "GraphosGame.h"

#include "File.h"

#include "GameObject.h"
#include "ScriptController.h"
#include "Physics.h"
#include "GraphicsController.h"
#include "AssetController.h"
#include "ShaderController.h"
#include "Input.h"
#include "Time.h"

#include <vector>
#include <string>
#include <json/json.h>
#include <cstdlib>

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
	Time::Get().Update();

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
			GraphicsController::Get().MessageLoop();

			// Update time
			Time::Get().Update();

			// Update input
			Input::Get().Update();

			// Update physics
			Physics::Physics::Get().Update();

			// Do the updating of the child class.
			Update();

			//////////////////////////////////////////////////////////////////////////
			// Draw
			//////////////////////////////////////////////////////////////////////////

			// Begin drawing
			GraphicsController::Get().CallGLFunction( GraphicsController::BEGIN );

			// Draw in child class
			Draw();

			// End drawing
			GraphicsController::Get().CallGLFunction( GraphicsController::END );
		}
		catch (exception e)
		{
			WindowController::Get().DisplayMessage( e.what() );
		}
	}

	Stop();
}

void GraphosGame::Reset( void )
{
	Config::Get().LoadSettings();
	GraphicsController::Get().Reload();

	// Call child shutdown
	Shutdown();

	// Shutdown UI and controllers
	delete ui;
	Physics::Physics::Get().Shutdown();
	AssetController::Get().Shutdown();
	ScriptController::Get().Shutdown();

	// Restart
	ScriptController::Get().Initialize();
	AssetController::Get().Initialize();
	Physics::Physics::Get().Initialize();
	Input::Get().ui = ui = new UserInterface( this );

	CurrentState = GameState::Menu;

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

	Config::Get().LoadSettings();

	GraphicsController::Get().Initialize();

	AssetController::Get().Initialize();

	Physics::Physics::Get().Initialize();

	ScriptController::Get().Initialize();

	Input::Get().ui = ui = new UserInterface( this );

	Initialize();
}

void GraphosGame::Stop( void )
{
	// Call child shutdown
	Shutdown();

	// Shutdown UI and controllers
	delete ui;
	Physics::Physics::Get().Shutdown();
	AssetController::Get().Shutdown();
	ScriptController::Get().Shutdown();
}