#ifndef __WINDOW_CONTROLLER
#define __WINDOW_CONTROLLER

#include "Win32Controller.h"

namespace Graphos
{
	namespace Graphics
	{
		class WindowController
		{
		public:
#if defined( _WIN32 )
			static
			Win32Controller&	Get( void )
			{
				return Core::ISingleton<Win32Controller>::Get();
			}
#elif defined( __APPLE__ )
			static
			OSXController&		Get( void )
			{
				return Core::IController<OSXController>::Get();
			}
#endif//_WIN32||__APPLE__

		private:
								WindowController( void ) { }
								WindowController( const WindowController& );
			void				operator=( const WindowController& );
		};
	}
}

#endif//__WINDOW_CONTROLLER