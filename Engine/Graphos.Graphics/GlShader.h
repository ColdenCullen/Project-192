#ifndef __GL_SHADER
#define __GL_SHADER

#include <unordered_map>
#include <string>
#include <Gl/GLIncludes.h>
#include "Matrix4.h"
#include "IShader.h"
#include "OutputController.h"

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

			void				Shutdown( void ) override { IShader::Shutdown(); }
			void				Draw( Core::Mesh& mesh ) const override;
			void				BindTexture( Core::Texture& text ) const override;

			void				RegisterConstBuffer( std::string name, ConstBuffer* buf ) override;

			void				SetUniform( std::string name, const gFloat value ) const override;
			void				SetUniform( std::string name, const int value ) const override;
			void				SetUniformArray( std::string name, const gFloat* value, const int size ) const override;
			void				SetUniformArray( std::string name, const int* value, const int size ) const override;
			void				SetUniformBuffer( std::string name, const gByte* value, const size_t size ) const override 
			{
				Utility::OutputController::PrintMessage(Utility::OutputType::OT_WARNING, "SetUniformBuffer not implemented in GlShader");
			}
			void				SetUniformMatrix( std::string name, const Math::Matrix4& matrix ) const;

		private:
			std::unordered_map<std::string, unsigned int>
								uniforms;

			void				ScanForVars( std::string vertexBody, std::string fragmentBody );
			void				Compile( std::string vertexBody, std::string fragmentBody );

		};
	}
}

#endif//__GL_SHADER