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
								SpotLight( std::string name, 
											Math::Vector3 initPos = Math::Vector3(),
											gFloat initInnerAngle = 30,
											gFloat initOuterAngle = 30,
											gFloat initFallOffRadius = 1,
											Math::Vector3 initDir = Math::Vector3(),
											Math::Vector4 initColor = Math::Vector4(),
											GameObject* owner = nullptr )
											: position( initPos ), innerAngle( initInnerAngle ),
											outerAngle( initOuterAngle ), fallOffRadius( initFallOffRadius ),
											DirectionalLight( name, initDir, initColor, owner ) { }
								~SpotLight( void ) { }

			void				Update( void ) override;
			void				Draw( Graphics::IShader* shader ) override;

			Math::Vector3		position;
			gFloat				innerAngle;
			gFloat				outerAngle;
			gFloat				fallOffRadius;
		};
	}

}
#endif
