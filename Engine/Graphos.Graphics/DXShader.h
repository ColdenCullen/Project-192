#ifndef __DXSHADER
#define __DXSHADER

#include <string>
#include <unordered_map>
#include <utility>
#include "IShader.h"
#include <DirectX/DirectXIncludes.h>

namespace Graphos
{
	namespace Graphics
	{
		struct DxConstBuffer : public ConstBuffer
		{
			DirectX::ID3D11Buffer* vsConstantBuffer;
			char*			data;

			DxConstBuffer( void ) : ConstBuffer() { }

			~DxConstBuffer( void )
			{
				delete[] data;
				ReleaseCOMobjMacro( vsConstantBuffer );
			}
		};

		class DXShader : public IShader
		{
		public:
								DXShader( std::string vertexPath, std::string fragmentPath );
								~DXShader(void);

			void				RegisterConstBuffer( std::string name, ConstBuffer* buf ) override;

			void				Shutdown( void ) override;
			void				Draw( Core::Mesh& mesh ) const override;
			void				BindTexture( Core::Texture& text ) const override;

			void				SetUniform( std::string name, const float value ) const override;
			void				SetUniform( std::string name, const int value ) const override;
			void				SetUniformArray( std::string name, const float* value, const int size ) const override;
			void				SetUniformArray( std::string name, const int* value, const int size ) const override;
			void				SetUniformMatrix( std::string name, const Math::Matrix4& matrix ) const override;
			
		private:
			// Shaders
			DirectX::ID3D11VertexShader* vertexShader;
			DirectX::ID3D11PixelShader*  pixelShader;

			// other data for the shader
			DirectX::ID3D11InputLayout*  vertexLayout;
			DirectX::ID3D11SamplerState* samplerState;

			DxConstBuffer*		buffer;
		};
	}
}

#endif//__DXSHADER
