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

			void				Update( void ) {  }
			void				Draw( void );
			void				Shutdown( void );

		private:
			unsigned int		textureID;
			unsigned int		width;
			unsigned int		height;
		};
	}
}

#endif//__TEXTURE