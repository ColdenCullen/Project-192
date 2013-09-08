#ifndef _MODEL_H_
#define _MODEL_H_

#include <string>

#include "IComponent.h"

namespace Graphos
{
	namespace Core
	{
		class Mesh : public IComponent
		{
		public:
								Mesh( void ) { }
								Mesh( std::string filePath ) { LoadFromFile( filePath ); }

			void				LoadFromFile( std::string filePath );

			void				Update( void ) { } 
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