#include "stdafx.h"

// Windows ONLY
#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
//#include <Windows.h>
#include "Resource.h"

#include "WindowController.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Graphics;

// Window styles
#define GWS_FULLSCREEN ( WS_POPUP | WS_SYSMENU )
#define GWS_WINDOWED ( WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU )

void Win32Controller::Initialize( void )
{
	screenWidth = GetSystemMetrics( SM_CXSCREEN );
	screenHeight = GetSystemMetrics( SM_CYSCREEN );

	fullScreen = Config::Get().GetData<bool>( "display.fullscreen" );
	if( fullScreen )
	{
		width	= screenWidth;
		height	= screenHeight;

		Config::Get().SetData( "display.width", screenWidth );
		Config::Get().SetData( "display.height", screenHeight );
	}
	else
	{
		width	= Config::Get().GetData<unsigned int>( "display.width" );
		height	= Config::Get().GetData<unsigned int>( "display.height" );
	}

	if( !fullScreen && ( width <= 0 || height <= 0 ) )
		throw exception( "Display settings invalid" );

	unsigned int formatCount;
	int pixelFormat[1];
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;

	hInstance = GetModuleHandle( NULL );

	// Initialize global strings
	WNDCLASSEX wcex;

	wcex.cbSize			= sizeof( WNDCLASSEX );
	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc	= &Win32Controller::WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon( hInstance, MAKEINTRESOURCE( IDI_GRAPHOSGRAPHICS ) );
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= L"Graphos";
	wcex.hIconSm		= LoadIcon( hInstance, MAKEINTRESOURCE( IDI_SMALL ) );

	RegisterClassEx( &wcex );

	// Perform application initialization:
	hWnd = CreateWindow( L"Graphos", L"Graphos", fullScreen ? GWS_FULLSCREEN : GWS_WINDOWED,
		( screenWidth - this->width ) / 2, ( screenHeight - this->height ) / 2, this->width, this->height,
		NULL, NULL, hInstance, NULL );
	if( !hWnd )
		throw exception( "Error opening init window." );

	ShowWindow( hWnd, SW_HIDE );

	// Get device context
	deviceContext = GetDC( hWnd );
	if( !deviceContext )
		throw exception( "Error getting device context." );

	// Set the pixel format
	if( !SetPixelFormat( deviceContext, 1, &pixelFormatDescriptor ) )
		throw exception( "Error setting pixel format." );

	renderContext = wglCreateContext( deviceContext );
	if( !renderContext )
		throw exception( "Error getting render context." );

	if( !wglMakeCurrent( deviceContext, renderContext ) )
		throw exception( "Error setting contexts." );

	glewExperimental = GL_TRUE;
	GLenum result = glewInit();

	// Delete temp window
	Shutdown();

	// Create new permanent window
	hWnd = CreateWindow( L"Graphos", L"Graphos", fullScreen ? GWS_FULLSCREEN : GWS_WINDOWED,
		( screenWidth - this->width ) / 2, ( screenHeight - this->height ) / 2, this->width, this->height,
		NULL, NULL, hInstance, NULL );
	if( !hWnd )
		throw exception( "Error opening window." );

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
	deviceContext = GetDC( hWnd );
	if( !deviceContext )
		throw exception( "Error getting device context." );

	// Query pixel format
	if( wglChoosePixelFormatARB( deviceContext, attributeList, NULL, 1, pixelFormat, &formatCount ) == -1 )
		throw exception( "Error getting pixel format." );

	// Set the pixel format
	if( SetPixelFormat( deviceContext, *pixelFormat, &pixelFormatDescriptor ) == -1 )
		throw exception( "Error setting pixel format." );

	// Create OpenGL rendering context
	renderContext = wglCreateContextAttribsARB( deviceContext, NULL, versionInfo );
	if( !renderContext )
		throw exception( "Error getting render context." );

	// Set current context
	if( !wglMakeCurrent( deviceContext, renderContext ) )
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

void Win32Controller::Shutdown( void )
{
	// Release contexts
	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( renderContext );
	renderContext = NULL;
	ReleaseDC( hWnd, deviceContext );
	deviceContext = NULL;

	if( IsWindow( hWnd ) )
	{
		DestroyWindow( hWnd );
		hWnd = NULL;
	}
}

void Win32Controller::Resize( bool fullScreen, unsigned int newWidth, unsigned int newHeight )
{
	if( !fullScreen && ( newWidth <= 0 || newHeight <= 0 ) )
		return;
	
	this->fullScreen = fullScreen;

	LONG style = GetWindowLong( hWnd, GWL_STYLE ) & ~( GWS_FULLSCREEN | GWS_WINDOWED );

	if( fullScreen )
	{
		width  = screenWidth;
		height = screenHeight;
		style |= GWS_FULLSCREEN;

		// Update config
		Config::Get().SetData( "display.width", screenWidth );
		Config::Get().SetData( "display.height", screenHeight );
	}
	else
	{
		width  = newWidth;
		height = newHeight;
		style |= GWS_WINDOWED;
	}

	SetWindowLong( hWnd, GWL_STYLE, style );
	SetWindowPos( hWnd, NULL, ( screenWidth - width ) / 2, ( screenHeight - height ) / 2, width + ( 2 * GetSystemMetrics( SM_CYBORDER ) ), height + GetSystemMetrics( SM_CYCAPTION ) + GetSystemMetrics( SM_CYBORDER ), SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED );
	ShowWindow( hWnd, SW_NORMAL );

	glViewport( 0, 0, width, height );

	perspectiveMatrix = Matrix4::BuildPerspective( (float)M_PI / 4.0f, (float)width / (float)height, 0.001f, 1000.0f );
	orthogonalMatrix  = Matrix4::BuildOrthogonal( (float)width, (float)height, 0.001f, 1000.0f );
}

void Win32Controller::Reload( void )
{
	Resize(
		Config::Get().GetData<bool>( "display.fullscreen" ),
		Config::Get().GetData<unsigned int>( "display.width" ),
		Config::Get().GetData<unsigned int>( "display.height" ) );

	// Enable back face culling
	if( Config::Get().GetData<bool>( "graphics.backfaceculling" ) )
	{
		glEnable( GL_CULL_FACE );
		glCullFace( GL_BACK );
	}

	// Turn on of off the vsync
	if( Config::Get().GetData<bool>( "graphics.vsync" ) )
		wglSwapIntervalEXT( true );
	else
		wglSwapIntervalEXT( false );
}

void Win32Controller::MessageLoop( void )
{
	MSG msg;

	// Initialize the message structure.
	ZeroMemory( &msg, sizeof(MSG) );

	// Handle the windows messages.
	while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
void Win32Controller::DisplayMessage( std::string message )
{
	MessageBox( hWnd, std::wstring( message.begin(), message.end() ).c_str(), L"Graphos Error", MB_OK );
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_DESTROY	- post a quit message and return
//
LRESULT CALLBACK Win32Controller::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message )
	{
	case WM_CLOSE:
	case WM_DESTROY:
	case WM_QUIT:
		PostQuitMessage( 0 );
		break;
		// If key down, send it to input
	case WM_KEYDOWN:
		Input::Get().KeyDown( (unsigned int)wParam );
		return 0;
		// If key up, send it to input
	case WM_KEYUP:
		Input::Get().KeyUp( (unsigned int)wParam );
		return 0;
		// On Mouse Event
	case WM_RBUTTONDOWN:
		Input::Get().KeyDown( VK_RBUTTON );
		return 0;
		// On Mouse Event
	case WM_RBUTTONUP:
		Input::Get().KeyUp( VK_RBUTTON );
		return 0;
		// On Mouse Event
	case WM_LBUTTONDOWN:
		Input::Get().KeyDown( VK_LBUTTON );
		return 0;
		// On Mouse Event
	case WM_LBUTTONUP:
		Input::Get().KeyUp( VK_LBUTTON );
		return 0;
		// If no change, send to default windows handler
	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}
	return 0;
}

#endif//_WIN32