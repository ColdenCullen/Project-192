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
								static IPlatformWindowController* Get();

		private:
								WindowController( void ) { }
								WindowController( const WindowController& );
			void				operator=( const WindowController& );
		};
	}
}

#endif//__WINDOW_CONTROLLER