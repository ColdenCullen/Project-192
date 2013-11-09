#ifndef __TEXTURE
#define __TEXTURE

#include "IComponent.h"
#include <string>


namespace DirectX
{
	struct ID3D11ShaderResourceView;
	struct ID3D11Resource;
}

namespace Graphos
{
	namespace Core
	{
		class Texture : public IComponent
		{
		protected:
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

		protected:
			unsigned int		width;
			unsigned int		height;

		};
	}
}

#endif//__TEXTURE