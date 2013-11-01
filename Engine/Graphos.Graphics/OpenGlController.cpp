#include "stdafx.h"
#include "OpenGlController.h"
#include "WindowController.h"
#include "Config.h"

#include "CgShader.h"

using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Graphics;
using namespace OpenGL;

void OpenGlController::Initialize( void )
{
	WindowController::Get()->Initialize();

	WindowController::Get()->OpenWindow();

	unsigned int formatCount;
	int pixelFormat[1];
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;

	// Get device context
	deviceContext.glDeviceContext = GetDC( Win32Controller::Get()->GetHWnd() );
	if( !deviceContext.glDeviceContext )
		throw exception( "Error getting device context." );

	// Set the pixel format
	if( !SetPixelFormat( deviceContext.glDeviceContext, 1, &pixelFormatDescriptor ) )
		throw exception( "Error setting pixel format." );

	renderContext = wglCreateContext( deviceContext.glDeviceContext );
	if( !renderContext )
		throw exception( "Error getting render context." );

	if( !wglMakeCurrent( deviceContext.glDeviceContext, renderContext ) )
		throw exception( "Error setting contexts." );

	glewExperimental = GL_TRUE;
	GLenum result = glewInit();

	WindowController::Get()->CloseWindow();
	WindowController::Get()->OpenWindow();

	// Set attributes list
	int attributeList[ 19 ] = {
		WGL_SUPPORT_OPENGL_ARB, TRUE,							// Support for OpenGL rendering
		WGL_DRAW_TO_WINDOW_ARB, TRUE,							// Support for rendering window
		WGL_ACCELERATION_ARB,	WGL_FULL_ACCELERATION_ARB,		// Support for hardware acceleration
		WGL_COLOR_BITS_ARB,		24,								// Support for 24bit color
		WGL_DEPTH_BITS_ARB,		24,								// Support for 24bit depth buffer
		WGL_DOUBLE_BUFFER_ARB,	TRUE,							// Support for double buffer
		WGL_SWAP_METHOD_ARB,	WGL_SWAP_EXCHANGE_ARB,			// Support for swapping buffers
		WGL_PIXEL_TYPE_ARB,		WGL_TYPE_RGBA_ARB,				// Support for RGBA pixel type
		WGL_STENCIL_BITS_ARB,	8,								// Support for 8 bit stencil buffer
		0														// Null terminate
	};

	// Set version to 4.0
	int versionInfo[ 5 ] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 0,
		0
	};

	// Get new Device Context
	deviceContext.glDeviceContext = GetDC( Win32Controller::Get()->GetHWnd() );
	if( !deviceContext.glDeviceContext )
		throw exception( "Error getting device context." );

	// Query pixel format
	if( wglChoosePixelFormatARB( deviceContext.glDeviceContext, attributeList, NULL, 1, pixelFormat, &formatCount ) == -1 )
		throw exception( "Error getting pixel format." );

	// Set the pixel format
	if( SetPixelFormat( deviceContext.glDeviceContext, *pixelFormat, &pixelFormatDescriptor ) == -1 )
		throw exception( "Error setting pixel format." );

	// Create OpenGL rendering context
	renderContext = wglCreateContextAttribsARB( deviceContext.glDeviceContext, NULL, versionInfo );
	if( !renderContext )
		throw exception( "Error getting render context." );

	// Set current context
	if( !wglMakeCurrent( deviceContext.glDeviceContext, renderContext ) )
		throw exception( "Error setting contexts." );

	// Set depth buffer
	glClearDepth( 1.0f );

	// Enable depth testing
	glEnable( GL_DEPTH_TEST );

	// Enable transparency
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	// Set front face
	glFrontFace( GL_CW );

	Reload();

	glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );
}

void OpenGlController::BeginDraw( void )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void OpenGlController::EndDraw( void )
{
	SwapBuffers( deviceContext.glDeviceContext );
}

void OpenGlController::Shutdown( void )
{
	// Release contexts
	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( renderContext );
	renderContext = NULL;
	ReleaseDC( Win32Controller::Get()->GetHWnd(), deviceContext.glDeviceContext );
	deviceContext.glDeviceContext = NULL;

}

void OpenGlController::Resize( void )
{
	glViewport( 0, 0, WindowController::Get()->GetWidth(), WindowController::Get()->GetHeight() );
}

void Graphos::Graphics::OpenGlController::Reload( void )
{
	Resize();

	// Enable back face culling
	if( Config::GetData<bool>( "graphics.backfaceculling" ) )
	{
		glEnable( GL_CULL_FACE );
		glCullFace( GL_BACK );
	}

	// Turn on of off the v sync
	wglSwapIntervalEXT( Config::GetData<bool>( "graphics.vsync" ) );
}
