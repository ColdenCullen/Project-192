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

								GlShader( void )
									: vertexShaderID( 0 ), fragmentShaderID( 0 ), programID( 0 ) { }
								GlShader( unsigned int vertex, unsigned int fragment, unsigned int program )
									: vertexShaderID( vertex ), fragmentShaderID( fragment ), programID( program ) { }

			GlShader&			Initialize( std::string vertexPath, std::string fragmentPath );
			void				Shutdown( void ) override { }
			void				Draw( const Core::Mesh& mesh ) const override;
			void				BindTexture( const Core::Texture& text ) const override;

			void				SetUniform( std::string name, int value ) const override;
			void				SetUniform( std::string name, float value ) const override;
			void				SetUniform( std::string name, const Math::Matrix4& value ) const;// override;

		private:
			std::unordered_map<std::string, unsigned int>
								uniforms;

			void				ScanForVars( std::string vertexBody );
			void				Compile( std::string vertexBody, std::string fragmentBody );

		};
	}
}

#endif//__GL_SHADER