#ifndef __TEXTURE
#define __TEXTURE

#include <string>
#include <D3D11.h>
#include <Cg/cgD3D11.h>
#include "DirectXTex\DirectXTex.h"

// Convenience macro for releasing a COM object
#ifndef ReleaseCOMobjMacro
	#define ReleaseCOMobjMacro( x ) { if( x ){  x->Release(); x = nullptr; } }
#endif

namespace Graphos
{
	namespace Core
	{
		class Texture 
		{
		public:
		Texture( void ) { }
		Texture( std::string filePath, ID3D11Device* device, CGprogram& myCgFragmentProgram ) { LoadFromFile( filePath, device, myCgFragmentProgram ); }

		void	LoadFromFile( std::string filePath, ID3D11Device* device, CGprogram& myCgFragmentProgram );

		void	Update( void ) { }
		void	Draw( void );
		void	Shutdown( void );

		private:
		ID3D11Resource* myDecalTexture;
		CGparameter myCgFragmentParam_decal;
		//CGparameter myCgFragmentParam_state;
		//unsigned int	textureID;
		//unsigned int	width;
		//unsigned int	height;
		};
	}
}

#endif//__TEXTURE