#ifndef __DIRECTIONAL_LIGHT
#define __DIRECTIONAL_LIGHT

#include "AmbientLight.h"

namespace Graphos
{
	namespace Core
	{

		class DirectionalLight : public AmbientLight
		{
		public:
								DirectionalLight( void );
								~DirectionalLight( void );

			Math::Vector3		direction;
			
		};
	}

}
#endif

