#ifndef _GRAPHICS_CONTROLLER_H_
#define _GRAPHICS_CONTROLLER_H_

#include "WindowController.h"
#include "IController.h"
#include "ISingleton.h"

namespace Graphos
{
	namespace Graphics
	{
		class GraphicsController : public Core::IController
		{
		public:
			// GL functions to call from outside project
			enum				GLFunctions : int { BEGIN, END };

			void				Initialize( void ) override;
			//TODO: Should probably implement this
			void				Shutdown( void ) override { }
			// Resizes display with given values
			void				Resize( bool fullScreen, unsigned int newWidth = 0, unsigned int newHeight = 0 );
			// Reloads display based on config settings
			void				Reload( void );
			void				CallGLFunction( GLFunctions function );

			void				MessageLoop( void ) { WindowController::Get().MessageLoop(); }

		private:
								GraphicsController( void ) { }
								GraphicsController( const GraphicsController& );
			void				operator=( const GraphicsController& );

			friend class		Core::ISingleton<GraphicsController>;
		};
	}
}

#endif//_GRAPHICS_CONTROLLER_H_