#ifndef __ILight
#define __ILight

#include "IComponent.h"
#include "Vector4.h"
#include "Vector3.h"

namespace Graphos
{
	namespace Core
	{
		class ILight : public IComponent
		{
		public:
			Math::Vector4 color;
		};
	}

}

#endif