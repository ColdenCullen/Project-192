#include "UserInterface.h"
#include "GraphosGame.h"
#include "WindowController.h"
#include "ShaderController.h"
#include "Input.h"
#include "Config.h"
#include "IShader.h"
#include "GraphicsController.h"

#include <string>
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>

#define NO_NAMESPACE
#include <GL/GLIncludes.h>

using namespace Awesomium;

using namespace Graphos;
using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Graphics;
using namespace Graphos::Utility;

UserInterface::UserInterface( GraphosGame* owner ) : owner( owner )
{
	char abspath[ 256 ];
#ifdef WIN32
	_fullpath( abspath, Config::GetData<std::string>( "ui.filePath" ).c_str(), MAX_PATH );
#else
	realpath( url.c_str(), abspath );
#endif

	// Get dimensions
	width  = Config::GetData<unsigned int>( "display.width" ) * Config::GetData<unsigned int>( "ui.scale.x" );
	height = Config::GetData<unsigned int>( "display.height" ) * Config::GetData<unsigned int>( "ui.scale.y" );

	// Initialize UI
	uiObj = new GameObject(ShaderController::GetShader( "texture" ));
	uiMesh = new Mesh("Resources/Assets/Meshes/UI.obj");
	uiObj->AddComponent(uiMesh);

	// Initialize Awesomium view
	view = new AwesomiumView( abspath, width, height );
	view->webView->set_js_method_handler( new JavaScriptHandler( this ) );

	while( view->webView->IsLoading() )
		WebCore::instance()->Update();

	// Set up JS hooks
	graphosGame = view->webView->CreateGlobalJavascriptObject( WSLit( "GraphosGame" ) ).ToObject();
	graphosGame.SetCustomMethod( WSLit( "ChangeState" ), false );
	graphosGame.SetCustomMethod( WSLit( "SetConfig" ), false );
	graphosGame.SetCustomMethod( WSLit( "Reset" ), false );

	// Scale the UI obj
	uiObj->transform->Scale(
		static_cast<float>(width) / 2.0f,
		static_cast<float>(height) / 2.0f,
		1.0f
	);

	// this pushes the top down on Windows, remove this code once problem fixed
	if( GraphicsController::GetActiveAdapter() == GraphicsAdapter::OpenGL &&
		!Config::GetData<bool>( "display.fullscreen" ) )
		uiObj->transform->Translate( 0.0f, -38.0f, 0.0f );

	// Focus for input
	view->webView->Focus();
}

/// Destructor
/// DO NOT CALL
UserInterface::~UserInterface()
{
	if( view )
	{
		view->Shutdown();
		delete view;
	}
}

/// Get input from the mouse
bool UserInterface::Update( void )
{
	Vector2 cursor = Input::GetMousePos();
	view->webView->InjectMouseMove(cursor.x, cursor.y);

	if( Input::IsKeyDown( VK_LBUTTON, true ) )
	{
		view->webView->InjectMouseDown( kMouseButton_Left );
	}
	else if( Input::IsKeyUp( VK_LBUTTON, true ) )
	{
		view->webView->InjectMouseUp( kMouseButton_Left );
	}

	view->Update();

	return true;
}

void UserInterface::Draw( void )
{
	ShaderController::GetShader( "texture" )->SetProjectionMatrix( WindowController::Get()->OrthogonalMatrix() );

	// Draw Awesomium
	view->Draw( ShaderController::GetShader( "texture" ) );

	// Draw mesh
	uiObj->Draw();	
}

void UserInterface::KeyPress( unsigned int key )
{
	// For the key down event
	// 0x0100 = WM_KEYDOWN
	WebKeyboardEvent keyDownEvent( 0x0100, key, NULL );

	// For the char entry
	WebKeyboardEvent keyCharEvent;
	keyCharEvent.type = WebKeyboardEvent::kTypeChar;
	// Get char
	char text[ 1 ] = { '1' };

#if defined( _WIN32 )
	text[ 0 ] = MapVirtualKey( key, MAPVK_VK_TO_CHAR );
#endif//_WIN32

	keyCharEvent.text[ 0 ] = text[ 0 ];

	// For the key up
	// 0x0101 = WM_KEYUP
	//WebKeyboardEvent keyUpEvent( 0x0101, key, NULL );

	if( view->webView )
	{
		view->webView->InjectKeyboardEvent( keyDownEvent );
		view->webView->InjectKeyboardEvent( keyCharEvent );
		//view->webView->InjectKeyboardEvent( keyUpEvent );
	}
}

void UserInterface::JavaScriptHandler::OnMethodCall( WebView* caller, unsigned int remoteObjectID, const WebString& methodName, const JSArray& args )
{
	// If called on GraphosGame
	if( remoteObjectID == owner->graphosGame.remote_id() )
	{
		if( methodName == WSLit( "ChangeState" ) && args.size() == 1 )
		{
			if( args[ 0 ].ToString() == WSLit( "Game" ) )
				owner->owner->CurrentState = GameState::Game;
			else if( args[ 0 ].ToString() == WSLit( "Menu" ) )
				owner->owner->CurrentState = GameState::Menu;
		}
		else if( methodName == WSLit( "SetConfig" ) && args.size() == 2 )
		{
			if( args[ 1 ].IsBoolean() )
				Config::SetData( ToString( args[ 0 ].ToString() ), args[ 1 ].ToBoolean() );
			else if( args[ 1 ].IsInteger() )
				Config::SetData( ToString( args[ 0 ].ToString() ), args[ 1 ].ToInteger() );
			else if( args[ 1 ].IsDouble() )
				Config::SetData( ToString( args[ 0 ].ToString() ), static_cast<float>( args[ 1 ].ToDouble() ) );
			else if( args[ 1 ].IsString() )
				Config::SetData( ToString( args[ 0 ].ToString() ), ToString( args[ 1 ].ToString() ) );
		}
		else if( methodName == WSLit( "Reset" ) && args.size() == 0 )
		{
			owner->owner->CurrentState = GameState::Reseting;
		}
	}
}

JSValue UserInterface::JavaScriptHandler::OnMethodCallWithReturnValue( WebView* caller, unsigned int remoteObjectID, const WebString& methodName, const JSArray& args )
{
	return JSValue::Undefined();
}