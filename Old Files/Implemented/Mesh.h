#ifndef _MODEL_H_
#define _MODEL_H_

#include <string>
#include <GL/GLIncludes.h>

#include "Ingredient.h"

#include "Vector3.h"
#include "Vector2.h"

namespace Graphos
{
	namespace Content
	{
		class Mesh : public Ingredient
		{
		public:
								Mesh( void ) { }
								Mesh( std::string filePath ) { LoadFromFile( filePath ); }

			bool				LoadFromFile( std::string filePath );

			bool				Update( float deltaTime ) { return true; } 
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