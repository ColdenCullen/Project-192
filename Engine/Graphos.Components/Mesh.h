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
			gUInt				numVertices;
			gUInt				numIndices;

			union VertexBuffer
			{
				gUInt					gl;
				DirectX::ID3D11Buffer*  dx;
			} vertexBuffer;

			union IndexBuffer
			{
				gUInt					gl;
				DirectX::ID3D11Buffer*  dx;
			} indexBuffer;

			// GL
			gUInt				vertexArrayObject;

		public:
			static gUInt		GetVertexSize( void ) { return sizeof(gFloat) * 8; }
								Mesh( void ) { }
								Mesh( std::string filePath ) { LoadFromFile( filePath ); }

			void				LoadFromFile( std::string filePath );

			void				Update( void ) override { }
			void				Draw( Graphics::IShader* shader ) override;
			void				Shutdown( void ) override;

			VertexBuffer&		GetVertexBuffer( void ) { return vertexBuffer; }
			IndexBuffer&		GetIndexBuffer( void )	{ return indexBuffer; }

			gUInt		 		GetNumVertices( void ) const { return numVertices; }
			gUInt				GetNumIndices( void ) const { return numIndices; }
			gUInt				GetGlVao( void ) const { return vertexArrayObject; }
			
		};
	}
}

#endif//_MODEL_H_
