#ifndef __SPOT_LIGHT
#define __SPOT_LIGHT

#include "DirectionalLight.h"

namespace Graphos
{
	namespace Core
	{

		class SpotLight : public DirectionalLight
		{
		public:
								SpotLight(void);
								~SpotLight(void);

			Math::Vector3		position;
			float				innerAngle;
			float				outerAngle;
			float				fallOffRadius;
		};
	}

}
#endif
