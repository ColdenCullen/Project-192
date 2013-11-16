#ifndef __AMBIENT_LIGHT
#define __AMBIENT_LIGHT

#include <string>

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
								AmbientLight( std::string name,
											Math::Vector4 initColor = Math::Vector4(), 
											GameObject* owner = nullptr );
									
								~AmbientLight( void ) { }

			virtual void		Update( void ) override;
			virtual void		Draw( Graphics::IShader* shader ) override;
			virtual void		Shutdown( void ) override;

			virtual gByte*		GetBuffer( void ) { return buffer; }
			int					GetSize( void ) { return size; }
			std::string			GetName( void ) { return name; }
			Math::Vector4		GetColor( void  ) { return color; }
			void				SetColor( const Math::Vector4& value ) { color = value; }

		protected:
			std::string			name;
			Math::Vector4		color;
			gByte*				buffer;
			int					size;
			bool				dirty;

		};
	}

}

#endif