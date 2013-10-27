
//#include "UserInterface.h"
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include "GraphosGame.h"
#include "WindowController.h"
#include "ShaderController.h"
#include "Input.h"
#include "Config.h"

//#include <string>


#define NO_NAMESPACE
#include <GL/GLIncludes.h>

using namespace Awesomium;

using namespace Graphos;
using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Graphics;

#define DEPTH 1.0f

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

	// Generate mesh
	numElements = 6;
	unsigned int indices[] = { 0, 1, 2, 0, 2, 3 };

	GLfloat floatWidth = static_cast<GLfloat>( width );
	GLfloat floatHeight = static_cast<GLfloat>( height );

	GLfloat vertices[] = {
		-floatWidth / 2.0f,	floatHeight / 2.0f,	DEPTH, 0.0f, 1.0f,
		-floatWidth / 2.0f,	-floatHeight / 2.0f,DEPTH, 0.0f, 0.0f,
		floatWidth / 2.0f,	-floatHeight / 2.0f,DEPTH, 1.0f, 0.0f,
		floatWidth / 2.0f,	floatHeight / 2.0f,	DEPTH, 1.0f, 1.0f
	};

	// Setup GL buffers
	glGenVertexArrays( 1, &vertexArrayObject );

	glBindVertexArray( vertexArrayObject );

	glGenBuffers( 1, &vertexBufferObject );

	glBindBuffer( GL_ARRAY_BUFFER, vertexBufferObject );
	glBufferData( GL_ARRAY_BUFFER, 6/*4*/ * 5 * sizeof( GLfloat ), vertices, GL_STATIC_DRAW );

	glEnableVertexAttribArray( 0 );// Position
	glEnableVertexAttribArray( 1 );// UV

	glBindBuffer( GL_ARRAY_BUFFER, vertexBufferObject );
	glVertexAttribPointer( 0, 3, GL_FLOAT, false, 5 * sizeof( GLfloat ), 0 );

	glBindBuffer( GL_ARRAY_BUFFER, vertexBufferObject );
	glVertexAttribPointer( 1, 2, GL_FLOAT, false, 5 * sizeof( GLfloat ), (unsigned char*)NULL + ( 3 * sizeof( GLfloat ) ) );

	glGenBuffers( 1, &indexBuffer );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBuffer );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, numElements * sizeof( unsigned int ), indices, GL_STATIC_DRAW );

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

	// Scale to fix Awesomium issue
	transform.Scale(
		ISingleton<Config>::Get().GetData<float>( "ui.scale.x" ),
		-ISingleton<Config>::Get().GetData<float>( "ui.scale.y" ),
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

bool UserInterface::Update( void )
{
	Vector2 cursor = ISingleton<Input>::Get().GetMousePos();

	// Transform for scale
	view->webView->InjectMouseMove(
		( width / 2 ) + ( ( ( width / 2 ) - cursor.x ) * -transform.Scale()->x ),
		( height / 2 ) + ( ( ( height / 2 ) - cursor.y ) * transform.Scale()->y )
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
	//ISingleton<ShaderController>::Get().GetShader( "texture" ).Use();
	ISingleton<ShaderController>::Get().GetShader( "texture" )->SetModelMatrix( transform.WorldMatrix() );
	//ISingleton<ShaderController>::Get().GetShader( "texture" )->SetUniform( "shaderTexture", 0, 1,  );
	ISingleton<ShaderController>::Get().GetShader( "texture" )->SetProjectionMatrix( WindowController::Get().OrthogonalMatrix() );

	view->Draw( nullptr );

	// Bind and draw buffer
	//glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBuffer );
	glBindVertexArray( vertexArrayObject );

	glDrawElements( GL_TRIANGLES, numElements, GL_UNSIGNED_INT, NULL );

	ISingleton<ShaderController>::Get().GetShader( "texture" )->SetProjectionMatrix( WindowController::Get().PerspectiveMatrix() );
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