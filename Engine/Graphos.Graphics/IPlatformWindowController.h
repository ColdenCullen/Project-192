#ifndef __IPLATFORM_WINDOW_CONTROLLER
#define __IPLATFORM_WINDOW_CONTROLLER

#include "Matrix4.h"

namespace Graphos
{
	namespace Graphics
	{
		class IPlatformWindowController
		{
		public:
			virtual void		Initialize( void ) { }
			virtual void		Shutdown( void ) { }

			virtual void		Resize( void ) { }
			virtual void		MessageLoop( void ) { }

			virtual void		OpenWindow( void ) { }
			virtual void		CloseWindow( void ) { }

			// Getters
			unsigned int		GetWidth( void )	{ return width; }
			unsigned int		GetHeight( void )	{ return height; }

			Math::Matrix4&		PerspectiveMatrix( void ) { return perspectiveMatrix; }
			Math::Matrix4&		OrthogonalMatrix( void ) { return orthogonalMatrix; }

		protected:
			unsigned int		width, screenWidth;
			unsigned int		height, screenHeight;
			bool				fullScreen;

			Math::Matrix4		perspectiveMatrix;
			Math::Matrix4		orthogonalMatrix;
		};
	}
}

#endif//__IPLATFORM_WINDOW_CONTROLLER