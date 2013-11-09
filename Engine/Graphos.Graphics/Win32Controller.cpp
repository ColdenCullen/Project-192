#include "stdafx.h"

// Windows ONLY
#ifdef _WIN32

#include "Config.h"
#include "Resource.h"
#include "Win32Controller.h"
#include "WindowController.h"
#include "OpenGlController.h"
#include "DirectXController.h"
#include "Input.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// Window styles
#define GWS_FULLSCREEN ( WS_POPUP | WS_SYSMENU )
#define GWS_WINDOWED ( WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU )

using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Graphics;

LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

Win32Controller* Win32Controller::Get()
{
	return static_cast<Win32Controller*>( WindowController::Get() );
}

void Win32Controller::Initialize( void )
{
	hInstance = GetModuleHandle( NULL );

	// Initialize global strings
	WNDCLASSEX wcex;
	wcex.cbSize			= sizeof( WNDCLASSEX );
	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc	= &WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon( hInstance, MAKEINTRESOURCE( IDI_GRAPHOSGRAPHICS ) );
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= _T("Graphos");
	wcex.hIconSm		= LoadIcon( hInstance, MAKEINTRESOURCE( IDI_SMALL ) );

	RegisterClassEx( &wcex );
}

void Win32Controller::Shutdown( void )
{
	CloseWindow();
}

void Win32Controller::Resize( void )
{
	LONG style = GetWindowLong( hWnd, GWL_STYLE ) & ~( GWS_FULLSCREEN | GWS_WINDOWED );

	screenWidth = GetSystemMetrics( SM_CXSCREEN );
	screenHeight = GetSystemMetrics( SM_CYSCREEN );

	fullScreen = Config::GetData<bool>( "display.fullscreen" );
	if( fullScreen )
	{
		width	= screenWidth;
		height	= screenHeight;
		style  |= GWS_FULLSCREEN;

		Config::SetData( "display.width", screenWidth );
		Config::SetData( "display.height", screenHeight );
	}
	else
	{
		width	= Config::GetData<unsigned int>( "display.width" );
		height	= Config::GetData<unsigned int>( "display.height" );
		style  |= GWS_WINDOWED;
	}

	if( !fullScreen && ( width <= 0 || height <= 0 ) )
		throw std::exception( "Display settings invalid" );

	SetWindowLong( hWnd, GWL_STYLE, style );
	SetWindowPos( hWnd, NULL, ( screenWidth - width ) / 2, ( screenHeight - height ) / 2, width + ( 2 * GetSystemMetrics( SM_CYBORDER ) ), height + GetSystemMetrics( SM_CYCAPTION ) + GetSystemMetrics( SM_CYBORDER ), SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED );
	ShowWindow( hWnd, SW_NORMAL );

	perspectiveMatrix = Matrix4::BuildPerspective( (float)M_PI / 4.0f, (float)width / (float)height, 0.001f, 1000.0f );
	orthogonalMatrix  = Matrix4::BuildOrthogonal( (float)width, (float)height, 0.001f, 1000.0f );
}

void Win32Controller::OpenWindow( void )
{
	Resize();

	// Create new permanent window
	hWnd = CreateWindow( L"Graphos", L"Graphos", fullScreen ? GWS_FULLSCREEN : GWS_WINDOWED,
		( screenWidth - this->width ) / 2, ( screenHeight - this->height ) / 2, this->width, this->height,
		NULL, NULL, hInstance, NULL );
	if( !hWnd )
		throw std::exception( "Error opening window." );

	ShowWindow( hWnd, SW_NORMAL );
}

void Win32Controller::CloseWindow( void )
{
	if( IsWindow( hWnd ) )
	{
		DestroyWindow( hWnd );
		hWnd = NULL;
	}
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

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_DESTROY	- post a quit message and return
//
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
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
		Input::KeyDown( (unsigned int)wParam );
		return 0;
		// If key up, send it to input
	case WM_KEYUP:
		Input::KeyUp( (unsigned int)wParam );
		return 0;
		// On Mouse Event
	case WM_RBUTTONDOWN:
		Input::KeyDown( VK_RBUTTON );
		return 0;
		// On Mouse Event
	case WM_RBUTTONUP:
		Input::KeyUp( VK_RBUTTON );
		return 0;
		// On Mouse Event
	case WM_LBUTTONDOWN:
		Input::KeyDown( VK_LBUTTON );
		return 0;
		// On Mouse Event
	case WM_LBUTTONUP:
		Input::KeyUp( VK_LBUTTON );
		return 0;
		// If no change, send to default windows handler
	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}
	return 0;
}

#endif//_WIN32
