#ifndef __POINT_LIGHT
#define __POINT_LIGHT

#include "ILight.h"

namespace Graphos
{
	namespace Core
	{

		class PointLight : public ILight
		{
		public:
								PointLight(void);
								~PointLight(void);

			Math::Vector3		position;
			float				fallOffRadius;
		};
	}

}
#endif
