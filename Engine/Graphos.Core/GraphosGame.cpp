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
	ISingleton<Time>::Get().Update();

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
			ISingleton<GraphicsController>::Get().MessageLoop();

			// Update time
			ISingleton<Time>::Get().Update();

			// Update input
			ISingleton<Input>::Get().Update();

			// Update physics
			ISingleton<Physics::Physics>::Get().Update();

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
		catch (exception e)
		{
			ISingleton<OutputController>::Get().PrintMessage( OutputType::OT_ERROR, e.what() );
			break;
		}
	}

	Stop();
}

void GraphosGame::Reset( void )
{
	ISingleton<Config>::Get().Initialize();
	ISingleton<GraphicsController>::Get().Reload();

	// Call child shutdown
	Shutdown();

	// Shutdown UI and controllers
	delete_s( ui );
	ISingleton<Physics::Physics>::Get().Shutdown();
	ISingleton<AssetController>::Get().Shutdown();
	ISingleton<ScriptController>::Get().Shutdown();

	// Restart<
	ISingleton<ScriptController>::Get().Initialize();
	ISingleton<AssetController>::Get().Initialize();
	ISingleton<Physics::Physics>::Get().Initialize();
	ISingleton<Input>::Get().ui = ui = new UserInterface( this );

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

	ISingleton<Config>::Get().Initialize();

	ISingleton<GraphicsController>::Get().Initialize();

	ISingleton<AssetController>::Get().Initialize();

	ISingleton<Physics::Physics>::Get().Initialize();

	ISingleton<ScriptController>::Get().Initialize();

	ISingleton<Input>::Get().ui = ui = new UserInterface( this );

	Initialize();
}

void GraphosGame::Stop( void )
{
	// Call child shutdown
	Shutdown();

	// Shutdown UI and controllers
	delete_s( ui );
	ISingleton<ShaderController>::Get().Shutdown();
	ISingleton<Physics::Physics>::Get().Shutdown();
	ISingleton<AssetController>::Get().Shutdown();
	ISingleton<ScriptController>::Get().Shutdown();
}