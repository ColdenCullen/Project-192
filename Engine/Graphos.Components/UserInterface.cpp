#include "UserInterface.h"
#include "GraphosGame.h"
#include "WindowController.h"
#include "ShaderController.h"
#include "Input.h"
#include "Config.h"

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

UserInterface::UserInterface( GraphosGame* owner ) : owner( owner )
{
	char abspath[ 256 ];
#ifdef WIN32
	_fullpath( abspath, ISingleton<Config>::Get().GetData<std::string>( "ui.filePath" ).c_str(), MAX_PATH );
#else
	realpath( url.c_str(), abspath );
#endif

	// Get dimensions
	width = ISingleton<Config>::Get().GetData<unsigned int>( "display.width" );
	height = ISingleton<Config>::Get().GetData<unsigned int>( "display.height" );

	// Initialize mesh
	uiObj = new GameObject(ISingleton<ShaderController>::Get().GetShader( "simple" ));
	uiMesh = new Mesh("Resources/Assets/Meshes/UI.obj");
	uiObj->AddComponent(uiMesh);
	//uiMesh().LoadFromFile("Resources/Assets/Meshes/UI.obj");
	//objects.LoadObjects( "" );
	//uiMesh = objects.GetObjectByName( "UI" );

	// Initialize Awesomium view
	view = new AwesomiumView( abspath, width, height );
	view->webView->set_js_method_handler( new JavaScriptHandler( this ) );

	while( view->webView->IsLoading() )
		WebCore::instance()->Update();

	graphosGame = view->webView->CreateGlobalJavascriptObject( WSLit( "GraphosGame" ) ).ToObject();
	graphosGame.SetCustomMethod( WSLit( "ChangeState" ), false );
	graphosGame.SetCustomMethod( WSLit( "SetConfig" ), false );
	graphosGame.SetCustomMethod( WSLit( "Reset" ), false );

	width	= static_cast<float>( width )  * ISingleton<Config>::Get().GetData<float>( "ui.scale.x" );
	height	= static_cast<float>( height ) * ISingleton<Config>::Get().GetData<float>( "ui.scale.y" );

	// Scale the UI obj
	transform.Scale(
		width,
		-1 * height,
		1.0f
	);

	// Focus for input
	view->webView->Focus();
}

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
	Vector2 cursor = ISingleton<Input>::Get().GetMousePos();

	// Transform for scale
	view->webView->InjectMouseMove(
		( width / 2 ) + ( ( ( width / 2 ) - cursor.x ) * -transform.Scale().x ),
		( height / 2 ) + ( ( ( height / 2 ) - cursor.y ) * transform.Scale().y )
	);

	if( ISingleton<Input>::Get().IsKeyDown( VK_LBUTTON, true ) )
	{
		view->webView->InjectMouseDown( kMouseButton_Left );
	}
	else if( ISingleton<Input>::Get().IsKeyUp( VK_LBUTTON, true ) )
	{
		view->webView->InjectMouseUp( kMouseButton_Left );
	}

	view->Update();

	return true;
}

void UserInterface::Draw( void )
{
	ISingleton<ShaderController>::Get().GetShader( "simple" )->SetModelMatrix( transform.WorldMatrix() );
	ISingleton<ShaderController>::Get().GetShader( "simple" )->SetUniform( "shaderTexture", 0 );
	ISingleton<ShaderController>::Get().GetShader( "simple" )->SetProjectionMatrix( WindowController::Get().OrthogonalMatrix() );

	// Draw Awesomium
	view->Draw( nullptr );

	// Draw mesh
	uiObj->Draw();

	ISingleton<ShaderController>::Get().GetShader( "simple" )->SetProjectionMatrix( WindowController::Get().PerspectiveMatrix() );
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
				ISingleton<Config>::Get().SetData( ToString( args[ 0 ].ToString() ), args[ 1 ].ToBoolean() );
			else if( args[ 1 ].IsInteger() )
				ISingleton<Config>::Get().SetData( ToString( args[ 0 ].ToString() ), args[ 1 ].ToInteger() );
			else if( args[ 1 ].IsDouble() )
				ISingleton<Config>::Get().SetData( ToString( args[ 0 ].ToString() ), static_cast<float>( args[ 1 ].ToDouble() ) );
			else if( args[ 1 ].IsString() )
				ISingleton<Config>::Get().SetData( ToString( args[ 0 ].ToString() ), ToString( args[ 1 ].ToString() ) );
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