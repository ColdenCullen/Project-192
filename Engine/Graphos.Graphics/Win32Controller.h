#if !defined( __WIN32_CONTROLLER ) && defined( _WIN32 )
#define __WIN32_CONTROLLER

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "WindowController.h"

namespace Graphos
{
	namespace Graphics
	{
		class Win32Controller : public WindowController
		{
		public:
			static Win32Controller*	Get();

			void				Initialize( void ) override;
			void				Shutdown( void ) override;
			void				Resize( void ) override;
			void				MessageLoop( void ) override;
	
			void				OpenWindow( void ) override;
			void				CloseWindow( void ) override;

			HWND				GetHWnd( void ) { return hWnd; }

								Win32Controller( void ) { }

		private:
								//Win32Controller( void ) { }
								Win32Controller( Win32Controller& );
			Win32Controller&	operator=( const Win32Controller& );

			HINSTANCE			hInstance;						// Current Windows application instance
			HWND				hWnd;							// Current Windows window

			friend class		WindowController;
		};
	}
}

#endif//__WIN32_CONTROLLER/_WIN32
