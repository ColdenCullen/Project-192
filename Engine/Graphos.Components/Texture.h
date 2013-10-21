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
		public:
								Texture( void ) { }
								Texture( std::string filePath ) { LoadFromFile( filePath ); }
			
			void				LoadFromFile( std::string filePath );

			void				Draw( Graphics::IShader* shader ) override;
			void				Shutdown( void ) override;

			unsigned int		GetGlTextureId( void ) const { return glTextureId; }
			DirectX::ID3D11ShaderResourceView*	GetDxTextureId( void ) const { return dxTexture; }

		private:
			// OpenGL Texture ID
			unsigned int		glTextureId;

			// DirectX Texture Reference
			DirectX::ID3D11ShaderResourceView*		dxTexture;

			unsigned int		width;
			unsigned int		height;
		};
	}
}

#endif//__TEXTURE