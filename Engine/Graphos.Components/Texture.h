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
			
			bool				LoadFromFile( std::string filePath );

			bool				Update( void ) { return true; }
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