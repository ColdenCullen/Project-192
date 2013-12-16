#ifndef __SPOT_LIGHT
#define __SPOT_LIGHT

#include "DirectionalLight.h"
#include "PointLight.h"

namespace Graphos
{
	namespace Core
	{

		class SpotLight : public DirectionalLight, public PointLight
		{
		public:
								SpotLight( std::string name, 
											Math::Vector4 initPos,
											gFloat initInnerAngle,
											gFloat initOuterAngle,
											gFloat initRange,
											gFloat initConstAttenuation,
											gFloat initLinearAttenuation,
											gFloat initQuadAttenuation,
											Math::Vector4 initDir,
											Math::Vector4 initColor,
											GameObject* owner ) : DirectionalLight(name,initDir,initColor,owner),
											PointLight(name,initPos,initRange,initConstAttenuation,initLinearAttenuation,initQuadAttenuation,initColor,owner){};
								~SpotLight( void ) { }

			// Must be duplicated due to static size
			void				Draw( Graphics::IShader* shader ) override;


			const static gSize size;

		protected:
			virtual void		UpdateBuffer( void ) override;

			gFloat				innerAngle;
			gFloat				outerAngle;

		};
	}

}
#endif
