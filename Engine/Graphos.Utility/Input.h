#ifndef __INPUT
#define __INPUT

#ifdef _WIN32

#pragma region Keys
#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39

#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x60
#pragma endregion
#endif

#include "UserInterface.h"
#include "Vector2.h"
#include "Event.h"

#include <cstdint>
#include <functional>
#include <unordered_map>

#define TOTAL_SIZE 256
#define SPLIT 4
#define SIZE (TOTAL_SIZE / SPLIT)

namespace Graphos
{
	namespace Utility
	{
		/**
		 * @struct	InputState
		 *
		 * @brief	Struct to store key-states.
		 *
		 * @author	Colden Cullen
		 * @date	11/23/2013
		 */
		struct InputState
		{
		public:
			InputState&			operator=( const InputState& other );
			gBool				operator[]( const unsigned char index );

			/**
			 * @fn	gBool CheckState( const unsigned char keyCode ) const;
			 *
			 * @brief	Check state the state of a key code.
			 *
			 * @author	Colden Cullen
			 * @date	11/23/2013
			 *
			 * @param	keyCode	The key code.
			 *
			 * @return	The status of the key.
			 */
			gBool				CheckState( const unsigned char keyCode ) const;

			/**
			 * @fn	void SetState( const unsigned char keyCode, const gBool newValue );
			 *
			 * @brief	Sets a key's state.
			 *
			 * @author	Colden Cullen
			 * @date	11/23/2013
			 *
			 * @param	keyCode 	The key code.
			 * @param	newValue	The new value.
			 */
			void				SetState( const unsigned char keyCode, const gBool newValue );

			/**
			 * @fn	void Reset( void );
			 *
			 * @brief	Resets this object.
			 *
			 * @author	Colden Cullen
			 * @date	11/23/2013
			 */
			void				Reset( void );
		private:
			uint64_t			bits[ SPLIT ];
		};

		/**
		 * @class	InputController
		 *
		 * @brief	A controller for handling inputs.
		 *
		 * @author	Colden Cullen
		 * @date	11/23/2013
		 */
		class InputController
		{
		public:
			/**
			 * @typedef	Event<void, gUInt> KeyEvent
			 *
			 * @brief	Defines an alias representing the key event.
			 */
			typedef Event<void, gUInt> KeyEvent;

			/**
			 * @fn	static void Input::Update( void );
			 *
			 * @brief	Updates the current key states.
			 *
			 * @author	Colden Cullen
			 * @date	11/23/2013
			 */
			static void			Update( void );

			/**
			 * @fn	static void Input::AddKeyDownUp( KeyEvent::Delegate func );
			 *
			 * @brief	Adds a key up event to the keystates.
			 *
			 * @author	Colden Cullen
			 * @date	11/23/2013
			 *
			 * @param	func	The function to add.
			 */
			static void			AddKeyUpEvent( KeyEvent::Delegate func );

			/**
			 * @fn	static void Input::AddKeyDownEvent( KeyEvent::Delegate func );
			 *
			 * @brief	Adds a key down event to the keystates.
			 *
			 * @author	Colden Cullen
			 * @date	11/23/2013
			 *
			 * @param	func	The function.
			 */
			static void			AddKeyDownEvent( KeyEvent::Delegate func );

			/**
			 * @fn	static void Input::KeyDown( gUInt input );
			 *
			 * @brief	Sets a key to be down.
			 *
			 * @author	Colden Cullen
			 * @date	11/23/2013
			 *
			 * @param	input	The key to set.
			 */
			static void			KeyDown( gUInt input );

			/**
			 * @fn	static void Input::KeyUp( gUInt input );
			 *
			 * @brief	Sets a key to be up.
			 *
			 * @author	Colden Cullen
			 * @date	11/23/2013
			 *
			 * @param	input	The key to set.
			 */
			static void			KeyUp( gUInt input );

			/**
			 * @fn	static gBool Input::IsKeyDown( gUInt input, const gBool checkPrevious = false );
			 *
			 * @brief	Is the key down.
			 *
			 * @author	Colden Cullen
			 * @date	11/23/2013
			 *
			 * @param	input		 	The input.
			 * @param	checkPrevious	(Optional) Whether or not to make sure the key is newly down.
			 *
			 * @return	A gBool.
			 */
			static gBool		IsKeyDown( gUInt input, const gBool checkPrevious = false );

			/**
			 * @fn	static gBool Input::IsKeyUp( gUInt input, const gBool checkPrevious = false );
			 *
			 * @brief	Is the key up.
			 *
			 * @author	Colden Cullen
			 * @date	11/23/2013
			 *
			 * @param	input		 	The input.
			 * @param	checkPrevious	(Optional) Whether or not to make sure the key is newly down.
			 *
			 * @return	A gBool.
			 */
			static gBool		IsKeyUp( gUInt input, const gBool checkPrevious = false );

			/**
			 * @fn	static Math::Vector2 Input::GetMousePos( );
			 *
			 * @brief	Gets mouse position on the screen.
			 *
			 * @author	Colden Cullen
			 * @date	11/23/2013
			 *
			 * @return	The mouse position.
			 */
			static Math::Vector2 GetMousePos( /*Transform& camera, float zPlane*/ );

		private:
								InputController( void ) { }
								InputController( InputController& other );
			void				operator=( InputController& other );

			static KeyEvent		keyDown;
			static KeyEvent		keyUp;

			static InputState	keyState;
			static InputState	prevKeyState;
			static InputState	stage;
			static gBool		lmbDown, rmbDown;
		};
	}
}

#endif//__INPUT