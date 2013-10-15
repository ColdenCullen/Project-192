#ifndef __DIRECTIONAL_LIGHT
#define __DIRECTIONAL_LIGHT

#include "ILight.h"

namespace Graphos
{
	namespace Core
	{

		class DirectionalLight : public ILight
		{
		public:
								DirectionalLight(void);
								~DirectionalLight(void);

			Math::Vector3		direction;
			
		};
	}

}
#endif

