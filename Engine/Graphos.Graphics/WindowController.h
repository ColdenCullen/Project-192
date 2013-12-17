#ifndef __WINDOW_CONTROLLER
#define __WINDOW_CONTROLLER

#include "Matrix4.h"

namespace Graphos
{
	namespace Graphics
	{
		class WindowController
		{
		public:
			static WindowController* Get();
			
			virtual void		Initialize( void ) { }
			virtual void		Shutdown( void ) { }

			virtual void		Resize( void ) { }
			virtual void		MessageLoop( void ) { }

			virtual void		OpenWindow( void ) { }
			virtual void		CloseWindow( void ) { }

			// Getters
			gUInt				GetWidth( void )	{ return width; }
			gUInt				GetHeight( void )	{ return height; }

			Math::Matrix4&		PerspectiveMatrix( void ) { return perspectiveMatrix; }
			Math::Matrix4&		OrthogonalMatrix( void ) { return orthogonalMatrix; }

								WindowController( void ) { }

		protected:
			gUInt				width, screenWidth;
			gUInt				height, screenHeight;
			bool				fullScreen;

			Math::Matrix4		perspectiveMatrix;
			Math::Matrix4		orthogonalMatrix;

								//WindowController( void ) { }
								WindowController( const WindowController& );
			void				operator=( const WindowController& );
		};
	}
}

#endif//__WINDOW_CONTROLLER