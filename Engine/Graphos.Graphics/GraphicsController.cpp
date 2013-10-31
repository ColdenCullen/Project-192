#include "StdAfx.h"
#include "GraphicsController.h"
#include "ShaderController.h"
#include "Config.h"
#include "AdapterController.h"

#include "WindowController.h"

using namespace Graphos::Core;
using namespace Graphos::Graphics;

void GraphicsController::Initialize( void )
{
	UpdateGraphicsAdapter();

	AdapterController::Get()->Initialize();

	ShaderController::Initialize();
}

void GraphicsController::Resize( void )
{
	WindowController::Get()->Resize();
	AdapterController::Get()->Resize();
}

void GraphicsController::Reload( void )
{
	UpdateGraphicsAdapter();

	WindowController::Get()->Resize();
	AdapterController::Get()->Reload();
}

void GraphicsController::UpdateGraphicsAdapter( void )
{
	if( Config::GetData<std::string>( "graphics.Adapter" ) == "OpenGL" )
		activeAdapter = GraphicsAdapter::OpenGL;
	else if( Config::GetData<std::string>( "graphics.Adapter" ) == "DirectX" )
		activeAdapter = GraphicsAdapter::DirectX;
	else
		throw std::exception( "Invalid Graphics.Adapter specified." );
}

void GraphicsController::MessageLoop( void )
{
	WindowController::Get()->MessageLoop();
}

void GraphicsController::Shutdown( void )
{
	AdapterController::Get()->Shutdown();
}

GraphicsAdapter GraphicsController::activeAdapter;
