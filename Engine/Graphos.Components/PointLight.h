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
								PointLight( std::string name, 
											Math::Vector3 initPos = Math::Vector3(),
											gFloat initFallOffRadius = 1,
											Math::Vector4 initColor = Math::Vector4(),
											GameObject* owner = nullptr )
											: position( initPos ), fallOffRadius( initFallOffRadius ),
											AmbientLight( name, initColor, owner ) { }
								~PointLight( void ) { }

			void				Update( void ) override;
			void				Draw( Graphics::IShader* shader ) override;

			Math::Vector3		position;
			gFloat				fallOffRadius;
		};
	}

}
#endif
