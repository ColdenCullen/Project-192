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
								DirectionalLight( std::string name, Math::Vector3 initDir = Math::Vector3(),
												  Math::Vector4 initColor = Math::Vector4(),
												  GameObject* owner = nullptr)
												  : AmbientLight( name, initColor, owner), 
													direction( initDir) { }
								~DirectionalLight( void ) { }

			virtual void				Update( void ) override;
			virtual void				Draw( Graphics::IShader* shader ) override;

			Math::Vector3		direction;
			
		};
	}

}
#endif

