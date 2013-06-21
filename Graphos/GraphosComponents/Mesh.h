#ifndef _MODEL_H_
#define _MODEL_H_

#include <string>

#include "Component.h"

namespace Graphos
{
	namespace Core
	{
		class Mesh : public Component
		{
		public:
								Mesh( void ) { }
								Mesh( std::string filePath ) { LoadFromFile( filePath ); }

			bool				LoadFromFile( std::string filePath );

			bool				Update( void ) { return true; } 
			void				Draw( void );
			void				Shutdown( void );

		private:
			unsigned int		vertexBufferObject;
			unsigned int		vertexArrayObject;
			unsigned int		indexBuffer;
			unsigned int		numElements;
		};
	}
}

#endif//_MODEL_H_