#ifndef __TEXTURE
#define __TEXTURE

#include <string>
#include "IComponent.h"

namespace Graphos
{
	namespace Core
	{
		class Texture : public IComponent
		{
		public:
								Texture( void ) { }
								Texture( std::string filePath ) { LoadFromFile( filePath ); }
			
			void				LoadFromFile( std::string filePath );

			void				Draw( Graphics::IShader* shader ) override;
			void				Shutdown( void ) override;

			unsigned int		GetTextureId( void ) const { return textureID; }

		private:
			unsigned int		textureID;
			unsigned int		width;
			unsigned int		height;
		};
	}
}

#endif//__TEXTURE