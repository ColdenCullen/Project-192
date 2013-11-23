#include "Input.h"
#include "WindowController.h"
#include "Config.h"
#include "Win32Controller.h"

#define BIT_AT_KEY_STATE( pos ) ( 1 << ( pos % SIZE ) )

using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Graphics;
using namespace Graphos::Utility;

InputState& InputState::operator=( const InputState& other )
{
	for( int ii = 0; ii < SPLIT; ++ii )
		if( bits[ ii ] != other.bits[ ii ] )
			bits[ ii ] = other.bits[ ii ];

	return *this;
}

bool InputState::operator[]( const unsigned char index )
{
	return CheckState( index );
}

bool InputState::CheckState( const unsigned char keyCode ) const
{
	return ( bits[ keyCode / SIZE ] & BIT_AT_KEY_STATE( keyCode ) ) != 0;
}

void InputState::SetState( const unsigned char keyCode, const bool newValue )
{
	if( newValue )
	{
		bits[ keyCode / SIZE ] |=  BIT_AT_KEY_STATE( keyCode );
	}
	else
	{
		bits[ keyCode / SIZE ] &= ~BIT_AT_KEY_STATE( keyCode );
	}
}

void InputState::Reset( void )
{
	for( int ii = 0; ii < SPLIT; ++ii )
		bits[ ii ] = 0;
}

void InputController::Update( void )
{
	prevKeyState = keyState;
	keyState = stage;
	//stage.Reset();
}

void InputController::AddKeyUpEvent( KeyEvent::Delegate func )
{
	keyUp.AddFunction( func );
}

void InputController::AddKeyDownEvent( KeyEvent::Delegate func )
{
	keyDown.AddFunction( func );
}

// Called when keys are down
void InputController::KeyDown( unsigned int input )
{
	stage.SetState( input, true );

	if( ui && input != VK_LBUTTON && input != VK_RBUTTON )
		//if( IsKeyDown( input, true ) )
			ui->KeyPress( input );

	keyDown( input );
}

// Called when keys are up
void InputController::KeyUp( unsigned int input )
{
	stage.SetState( input, false );

	keyUp( input );
}

// Is key down?
bool InputController::IsKeyDown( unsigned int input, const bool checkPrevious )
{
	return keyState[ input ] && ( !checkPrevious || !prevKeyState[ input ] );
}

// Is key up?
bool InputController::IsKeyUp( unsigned int input, const bool checkPrevious )
{
	return !keyState[ input ] && ( !checkPrevious || prevKeyState[ input ] );
}

Vector2 InputController::GetMousePos( /*Transform& camera, float zPlane*/ )
{
#if defined( _WIN32 )
	/*
	Win32Controller& wc = WindowController::Get();

	const float ASPECT_FACTOR = ( zPlane - camera.position.z ) * .825f / wc.GetHeight();

	POINT i;
	GetCursorPos( &i );
	ScreenToClient( wc.GetHWnd(), &i );

	Point p( i.x, i.y );

	p.x -= wc.GetWidth() / 2;
	p.y -= wc.GetHeight() / 2;

	p.x *= ASPECT_FACTOR;
	p.y *= -ASPECT_FACTOR;

	p.x += camera.position.x;
	p.y += camera.position.y;

	return p;
	*/

	POINT i;
	GetCursorPos( &i );
	ScreenToClient( Win32Controller::Get()->GetHWnd(), &i );

	// Adjust for border
	if( !Config::GetData<bool>( "display.fullscreen" ) )
		i.x -= GetSystemMetrics( SM_CYBORDER );

	//i.y -= GetSystemMetrics( /*SM_CYCAPTION*/SM_CYBORDER );
	return Vector2( static_cast<float>( i.x ), static_cast<float>( i.y ) );
	
#elif defined( __APPLE__ )
	
	return Point( 0, 0 );
	
#endif
}

bool InputController::lmbDown;
bool InputController::rmbDown;
InputState InputController::stage;
InputState InputController::prevKeyState;
InputState InputController::keyState;
InputController::KeyEvent InputController::keyUp;
InputController::KeyEvent InputController::keyDown;
UserInterface* InputController::ui;