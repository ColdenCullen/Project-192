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
		private:
			// shared
			unsigned int		numVertices;

			union VertexBuffer
			{
				unsigned int			gl;
				DirectX::ID3D11Buffer*  dx;
			} vertexBuffer;

			union IndexBuffer
			{
				unsigned int			gl;
				DirectX::ID3D11Buffer*  dx;
			} indexBuffer;

			// GL
			unsigned int		vertexArrayObject;

		public:
			static unsigned int GetVertexSize( void ) { return sizeof(float) * 8; }
								Mesh( void ) { }
								Mesh( std::string filePath ) { LoadFromFile( filePath ); }

			void				LoadFromFile( std::string filePath );

			void				Update( void ) override { }
			void				Draw( Graphics::IShader* shader ) override;
			void				Shutdown( void ) override;

			VertexBuffer&		GetVertexBuffer( void ) { return vertexBuffer; }
			IndexBuffer&		GetIndexBuffer( void )	{ return indexBuffer; }

			unsigned int 		GetNumVertices( void ) const { return numVertices; }
			unsigned int		GetGlVao( void ) const { return vertexArrayObject; }
			
		};
	}
}

#endif//_MODEL_H_
