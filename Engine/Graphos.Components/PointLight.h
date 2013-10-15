#ifndef __POINT_LIGHT
#define __POINT_LIGHT

#include "AmbientLight.h"

namespace Graphos
{
	namespace Core
	{

		class PointLight : public AmbientLight
		{
		public:
								PointLight( void );
								~PointLight( void );

			Math::Vector3		position;
			float				fallOffRadius;
		};
	}

}
#endif
