#ifndef __DXSHADER
#define __DXSHADER

#include <string>
#include <unordered_map>
#include <utility>
#include <v8/v8.h>
#include "IShader.h"
#include <DirectX/DirectXIncludes.h>

namespace Graphos
{
	namespace Graphics
	{
		class DXShader : public IShader
		{
		public:
								DXShader( std::string vertexPath, std::string fragmentPath );
								~DXShader(void);

			void				RegisterConstBuffer( v8::Arguments args );

			void				Shutdown( void ) override;
			void				Draw( const Core::Mesh& mesh ) const override;
			void				BindTexture( const Core::Texture& text ) const override;

			void				SetUniform( std::string name, const float value, ShaderType type ) const override;
			void				SetUniform( std::string name, const int value, ShaderType type ) const override;
			void				SetUniformArray( std::string name, const float* value, const int size, ShaderType type ) const override;
			void				SetUniformArray( std::string name, const int* value, const int size, ShaderType type ) const override;
			
		private:
			// Shaders
			DirectX::ID3D11VertexShader* vertexShader;
			DirectX::ID3D11PixelShader*  pixelShader;

			DirectX::ID3D11InputLayout*  vertexLayout;

			struct ConstBuffer
			{
				char*			data;
				std::unordered_map<std::string, std::pair<unsigned int, std::size_t>>
								meta;
			};

			ConstBuffer buffer;
		};
	}
}

#endif//__DXSHADER
