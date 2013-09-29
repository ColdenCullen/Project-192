#if !defined( __WIN32_CONTROLLER ) && defined( _WIN32 )
#define __WIN32_CONTROLLER

#include "ISingleton.h"
#include "IPlatformWindowController.h"

namespace Graphos
{
	namespace Graphics
	{
		class Win32Controller : public IPlatformWindowController
		{
		public:
			void				Initialize( void ) override;
			void				Shutdown( void ) override;
			void				Resize( void );
			void				MessageLoop( void );

			void				OpenWindow( void );
			void				CloseWindow( void );

			// Getters
			HWND				GetHWnd( void ) { return hWnd; }

		private:
								Win32Controller( void ) { }
								Win32Controller( Win32Controller& );
			Win32Controller&	operator=( const Win32Controller& );

			HINSTANCE			hInstance;						// Current Windows application instance
			HWND				hWnd;							// Current Windows window

			friend class		WindowController;
			friend class		Core::ISingleton<Win32Controller>;
		};
	}
}

#endif//__WIN32_CONTROLLER/_WIN32
