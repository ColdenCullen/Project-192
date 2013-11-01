#ifndef _MODEL_H_
#define _MODEL_H_

//#define NO_NAMESPACE
//#include <DirectX/DirectXIncludes.h>
//#undef NO_NAMESPACE
namespace DirectX
{
		struct ID3D11Buffer;
}
#include "IComponent.h"
#include "IShader.h"

//#include <string> in IShader.h

namespace Graphos
{
	namespace Core
	{
		class Mesh : public IComponent
		{
		public:
			static unsigned int GetVertexSize( void ) { return sizeof(float) * 8; }
								Mesh( void ) { }
								Mesh( std::string filePath ) { LoadFromFile( filePath ); }

			void				LoadFromFile( std::string filePath );

			void				Update( void ) override { }
			void				Draw( Graphics::IShader* shader ) override;
			void				Shutdown( void ) override;

			unsigned int 		GetNumVertices( void ) const { return numVertices; }
			unsigned int		GetVAO( void ) const { return vertexArrayObject; }
			unsigned int		GetIndexBuffer( void ) const { return indexBuffer; }

			DirectX::ID3D11Buffer*		GetVertexBuffer( void ) const { return vertexBuffer; }

		private:
			// shared
			unsigned int		numVertices;

			// GL
			unsigned int		vertexBufferObject;
			unsigned int		vertexArrayObject;
			unsigned int		indexBuffer;
			
			// Dx
			DirectX::ID3D11Buffer*		vertexBuffer;
		};
	}
}

#endif//_MODEL_H_