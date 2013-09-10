#include "StdAfx.h"
#include "GraphicsController.h"
#include "ShaderController.h"
#include "Config.h"

using namespace Graphos::Core;
using namespace Graphos::Graphics;

void GraphicsController::Initialize( void )
{
	WindowController::Get().Initialize();

	ISingleton<ShaderController>::Get().Initialize();
}

void GraphicsController::Resize( bool fullScreen, unsigned int newWidth, unsigned int newHeight )
{
	WindowController::Get().Resize( fullScreen, newWidth, newHeight );
	//OpenGLController::Get().Resize( newWidth, newHeight );
}

void GraphicsController::Reload( void )
{
	WindowController::Get().Reload();
}

void GraphicsController::CallGLFunction( GLFunctions function )
{
	switch( function )
	{
	case BEGIN:
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		break;
	case END:
#ifdef _WIN32
		SwapBuffers( WindowController::Get().GetDeviceContext() );
#endif
		break;
	}
}