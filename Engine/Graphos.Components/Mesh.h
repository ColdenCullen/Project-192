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
			unsigned int		GetGlVao( void ) const { return vertexArrayObject; }
			unsigned int		GetGlIndexBuffer( void ) const { return indexBuffer.glIndexBuffer; }

			DirectX::ID3D11Buffer*		GetDxVertexBuffer( void ) const { return vertexBuffer.dxVertexBuffer; }
			DirectX::ID3D11Buffer*		GetDxIndexBuffer( void ) const { return indexBuffer.dxIndexBuffer; }

		private:
			// shared
			unsigned int		numVertices;
			union
			{
				unsigned int			glVertexBuffer;
				DirectX::ID3D11Buffer*  dxVertexBuffer;
			} vertexBuffer;
			union
			{
				unsigned int			glIndexBuffer;
				DirectX::ID3D11Buffer*  dxIndexBuffer;
			} indexBuffer;

			// GL
			unsigned int		vertexArrayObject;
			
		};
	}
}

#endif//_MODEL_H_