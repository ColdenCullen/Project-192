#ifndef __TEXTURE
#define __TEXTURE

#include <string>
#include "Component.h"

namespace Graphos
{
	namespace Core
	{
		class Texture : public Component
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