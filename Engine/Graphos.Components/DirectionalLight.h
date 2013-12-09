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
								DirectionalLight( std::string name, Math::Vector3 initDir,
												  Math::Vector4 initColor,
												  GameObject* owner);
								~DirectionalLight( void ) { }
			
			// Must be duplicated due to static size
			virtual void		Draw( Graphics::IShader* shader ) override;

			Math::Vector3		GetDirection( void ) { return direction; }
			void				SetDirection( const Math::Vector3& value ) { dirty = true; direction = value; }

			const static gSize size;

		protected:

			virtual void		UpdateBuffer( void ) override;
			Math::Vector3		direction;
		};
	}

}
#endif

