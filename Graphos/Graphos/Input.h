#ifndef __INPUT
#define __INPUT

#ifdef _WIN32
//#include "stdafx.h"

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

#include <stdint.h>
#include "Vector2.h"

#define TOTAL_SIZE 256
#define SPLIT 4
#define SIZE (TOTAL_SIZE / SPLIT)

namespace Graphos
{
	// Forward declarations
	namespace Core
	{
		class UserInterface;
	}

	namespace Graphics
	{
		// Struct to store key-states
		struct InputState
		{
		public:
			InputState&			operator=( const InputState& other );
			bool				operator[]( const unsigned char index );

			bool				CheckState( const unsigned char keyCode ) const;
			void				SetState( const unsigned char keyCode, const bool newValue );
			void				Reset( void );
		private:
			uint64_t			bits[ SPLIT ];
		};

		class Input
		{
		public:
			Graphos::Core::UserInterface*
								ui;

			static Input& Get( void )
			{
				static Input instance;
				return instance;
			}

			void				Update( void );

			void				KeyDown( unsigned int input );
			void				KeyUp( unsigned int input );

			bool				IsKeyDown( unsigned int input, const bool checkPrevious = false );
			bool				IsKeyUp( unsigned int input, const bool checkPrevious = false );

			Graphos::Math::Vector2
								GetMousePos( /*Transform& camera, float zPlane*/ ) const;

		private:
								Input( void ) { }
								Input( Input& other );
			void				operator=( Input& other );

			InputState			keyState;
			InputState			prevKeyState;
			InputState			stage;
			bool				lmbDown, rmbDown;
		};
	}
}

#endif//__INPUT