#ifndef __IGRAPHICS_ADAPTER_CONTROLLER
#define __IGRAPHICS_ADAPTER_CONTROLLER

#include "IController.h"

namespace Graphos
{
	namespace Graphics
	{
		class IGraphicsAdapterController : public Core::IController
		{
		public:
			virtual void		Initialize( void ) override = 0;
			virtual void		Shutdown( void ) override = 0;

			virtual void		Resize( void ) = 0;
			virtual void		Reload( void ) = 0;

			virtual void		BeginDraw( void ) = 0;
			virtual void		EndDraw( void ) = 0;
		};
	}
}

#endif//__IGRAPHICS_ADAPTER_CONTROLLER