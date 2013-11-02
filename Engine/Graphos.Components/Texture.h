#ifndef __TEXTURE
#define __TEXTURE

#include "IComponent.h"
#include <string>


namespace DirectX
{
	struct ID3D11ShaderResourceView;
}

namespace Graphos
{
	namespace Core
	{
		class Texture : public IComponent
		{
		private:
			union TextureID
			{
				unsigned int gl;
				DirectX::ID3D11ShaderResourceView* dx;
			} textureId;

		public:
								Texture( void ) { }
								Texture( std::string filePath ) { LoadFromFile( filePath ); }
			
			void				LoadFromFile( std::string filePath );

			void				Draw( Graphics::IShader* shader ) override;
			void				Shutdown( void ) override;

			TextureID&			GetTextureId( void ) { return textureId; }

		private:
			unsigned int		width;
			unsigned int		height;
		};
	}
}

#endif//__TEXTURE