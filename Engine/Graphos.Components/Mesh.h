#ifndef _MODEL_H_
#define _MODEL_H_

#include <string>

#include "IComponent.h"
#include "Shader.h"

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

			void				Update( void ) override { }
			void				Draw( Graphics::Shader* shader ) override;
			void				Shutdown( void ) override;

			unsigned int 		GetNumElements( void ) const { return numElements; }
			unsigned int		GetVAO( void ) const { return vertexArrayObject; }
			unsigned int		GetIndexBuffer( void ) const { return indexBuffer; }

		private:
			unsigned int		vertexBufferObject;
			unsigned int		vertexArrayObject;
			unsigned int		indexBuffer;
			unsigned int		numElements;
		};
	}
}

#endif//_MODEL_H_