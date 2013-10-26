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
								AmbientLight( Math::Vector4 initColor = Math::Vector4(), 
											  GameObject* owner = nullptr )
									: IComponent( owner ), color( initColor ) { }
								~AmbientLight( void ) { }

			virtual void		Update( void ) override;
			virtual void		Draw( Graphics::IShader* shader ) override;

			Math::Vector4		color;
		};
	}

}

#endif