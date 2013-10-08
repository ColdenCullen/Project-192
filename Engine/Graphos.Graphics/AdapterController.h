#ifndef __ADAPTER_CONTROLLER
#define __ADAPTER_CONTROLLER

#include "IGraphicsAdapterController.h"

namespace Graphos
{
	namespace Graphics
	{
		class AdapterController
		{
		public:
			static IGraphicsAdapterController* Get( void );
		};
	}
}

#endif//__ADAPTER_CONTROLLER
