#ifndef __WINDOW_CONTROLLER
#define __WINDOW_CONTROLLER

#include <GL/GLIncludes.h>

/*#ifdef _WIN32
 #include "Resource.h"
 #include "stdafx.h"
#endif*/

#include "Config.h"
#include "Input.h"
#include "Matrix4.h"

using namespace Graphos::Math;

namespace Graphos
{
	namespace Graphics
	{
#pragma region PlatformWindowController
		class PlatformWindowController
		{
		public:
			virtual bool		Initialize( void ) = 0;
			virtual void		Shutdown( void ) = 0;
			virtual void		Resize( bool fullScreen, unsigned int newWidth = 0, unsigned int newHeight = 0 ) = 0;
			virtual void		Reload( void ) = 0;
			virtual void		MessageLoop( void ) = 0;

			// Getters
			unsigned int		GetWidth( void )	{ return width; }
			unsigned int		GetHeight( void )	{ return height; }
			//GLDeviceContext&		GetDeviceContext( void ) { return deviceContext; }
			GLRenderContext&	RenderContext( void ) { return renderContext; }
			Matrix4&			PerspectiveMatrix( void ) { return perspectiveMatrix; }
			Matrix4&			OrthogonalMatrix( void ) { return orthogonalMatrix; }

		protected:
			unsigned int		width, screenWidth;
			unsigned int		height, screenHeight;
			bool				fullScreen;

			Matrix4				perspectiveMatrix;
			Matrix4				orthogonalMatrix;
			//GLDeviceContext	deviceContext;
			GLRenderContext		renderContext;
		};
#pragma endregion

#pragma region Win32Controller
#if defined( _WIN32 )
		class Win32Controller : public PlatformWindowController
		{
		public:
			bool				Initialize( void );
			void				Shutdown( void );
			void				Resize( bool fullScreen, unsigned int newWidth = 0, unsigned int newHeight = 0 );
			void				Reload( void );
			void				MessageLoop( void );

			// Getters
			HWND				GetHWnd( void ) { return hWnd; }

			friend class		WindowController;

			GLDeviceContext&	GetDeviceContext( void ) { return deviceContext; }

		private:
								Win32Controller( void ) { }
								Win32Controller( Win32Controller& );
			void				operator=( Win32Controller& );

			HINSTANCE			hInstance;						// Current Windows application instance
			HWND				hWnd;							// Current Windows window

			GLDeviceContext		deviceContext;

			static
			LRESULT CALLBACK	WndProc( HWND, UINT, WPARAM, LPARAM );
		};
#pragma endregion

#pragma region OSXController
#elif defined( __APPLE__ )
		class OSXController : public PlatformWindowController
		{
		public:
			bool				Initialize( void );
			void				Shutdown( void );
			void				Resize( bool fullScreen, unsigned int newWidth = 0, unsigned int newHeight = 0 );
			void				Reload( void );
			void				MessageLoop( void );
			//private:
		};
#endif//_WIN32||__APPLE__
#pragma endregion

#pragma region WindowController
		class WindowController
		{
		public:
#if defined( _WIN32 )
			static
			Win32Controller&	Get( void )
			{
				static Win32Controller instance;
				return instance;
			}
#elif defined( __APPLE__ )
			static
			OSXController&		Get( void )
			{
				static OSXController instance;
				return instance;
			}
#endif//_WIN32||__APPLE__

		private:
								WindowController( void ) { }
								WindowController( const WindowController& );
			void				operator=( const WindowController& );
		};
#pragma endregion
	}
}

#endif//__WINDOW_CONTROLLER