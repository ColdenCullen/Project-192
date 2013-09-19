#ifndef __TEXTURE
#define __TEXTURE

#include <string>
#include <D3D11.h>
#include <Cg/cgD3D11.h>
//#include "DirectXTex\DirectXTex.h"

namespace Graphos
{
	namespace Core
	{
		class Texture 
		{
		public:
		Texture( void ) { }
		Texture( std::string filePath ) { LoadFromFile( filePath ); }

		void	LoadFromFile( std::string filePath );

		void	Update( void ) { }
		void	Draw( void );
		void	Shutdown( void );

		private:
		ID3D11Resource* myDecalTexture;
		//unsigned int	textureID;
		unsigned int	width;
		unsigned int	height;
		};
	}
}

#endif//__TEXTURE