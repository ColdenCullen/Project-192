#ifndef __TEXTURE
#define __TEXTURE

#include <string>
#include <DirectX/DirectXIncludes.h>
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

			unsigned int		GetGlTextureId( void ) const { return glTextureId; }

		private:
			// OpenGL Texture ID
			unsigned int		glTextureId;

			// DirectX Texture Reference
			DirectX::ID3D11Resource*		dxTexture;

			unsigned int		width;
			unsigned int		height;
		};
	}
}

#endif//__TEXTURE