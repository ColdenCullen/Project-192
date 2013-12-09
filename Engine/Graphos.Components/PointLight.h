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
											Math::Vector3 initPos,
											gFloat initFallOffRadius,
											Math::Vector4 initColor,
											GameObject* owner = nullptr );
								~PointLight( void ) { }

			// Must be duplicated due to static size
			void				Draw( Graphics::IShader* shader ) override;

			Math::Vector3		GetPosition( void ) { return position; }
			void				SetPosition( const Math::Vector3& value ) { dirty = true; position = value; }
			gFloat				GetFalloffRadius( void ) { return fallOffRadius; }
			void				GetFalloffRadius( const gFloat value ) { dirty = true; fallOffRadius = value; }

			const static gSize size;
			
		protected:

			virtual void		UpdateBuffer( void ) override;
			Math::Vector3		position;
			gFloat				fallOffRadius;
		};
	}

}
#endif
