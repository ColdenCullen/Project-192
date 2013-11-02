#ifndef __GL_SHADER
#define __GL_SHADER

#include <unordered_map>
#include <string>
#include <Gl/GLIncludes.h>
#include "Matrix4.h"
#include "IShader.h"

namespace Graphos
{
	namespace Graphics
	{
		struct GlShader : public IShader
		{
		public:
			unsigned int		vertexShaderID;
			unsigned int		fragmentShaderID;
			unsigned int		programID;

								GlShader( std::string vertexPath, std::string fragmentPath );

			void				Shutdown( void ) override { }
			void				Draw( Core::Mesh& mesh ) const override;
			void				BindTexture( Core::Texture& text ) const override;

			void				BuildConstBuffer( v8::Arguments args );

			void				SetUniform( std::string name, const float value, ShaderType type ) const override;
			void				SetUniform( std::string name, const int value, ShaderType type ) const override;
			void				SetUniformArray( std::string name, const float* value, const int size, ShaderType type ) const override;
			void				SetUniformArray( std::string name, const int* value, const int size, ShaderType type ) const override;

		private:
			std::unordered_map<std::string, unsigned int>
								uniforms;

			void				ScanForVars( std::string vertexBody, std::string fragmentBody );
			void				Compile( std::string vertexBody, std::string fragmentBody );

		};
	}
}

#endif//__GL_SHADER