#ifndef __OPENGL_CONTROLLER
#define __OPENGL_CONTROLLER

#include "IGraphicsAdapterController.h"

#include <GL/glincludes.h>

namespace Graphos
{
	namespace Graphics
	{
		class OpenGlController : public IGraphicsAdapterController
		{
		public:
			virtual void		Initialize( void ) override;
			virtual void		Shutdown( void ) override;
			virtual void		Resize( void ) override;
			virtual void		Reload( void ) override;
			virtual void		BeginDraw( void );
			virtual void		EndDraw( void );

			OpenGL::GLRenderContext&	RenderContext( void )		{ return renderContext; }

		private:
			OpenGL::GLRenderContext		renderContext;

			friend class		AdapterController;
		};
	}
}

#endif//__OPENGL_CONTROLLER