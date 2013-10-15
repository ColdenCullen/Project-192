#ifndef __AMBIENT_LIGHT
#define __AMBIENT_LIGHT

#include "IComponent.h"
#include "Vector4.h"
#include "Vector3.h"

namespace Graphos
{
	namespace Core
	{
		class AmbientLight : public IComponent
		{
		public:
								AmbientLight( void );
								~AmbientLight( void );

			Math::Vector4		color;
		};
	}

}

#endif