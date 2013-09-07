#ifndef __GL_SHADER
#define __GL_SHADER

#include <unordered_map>
#include <string>
#include <Gl/GLIncludes.h>
#include "Matrix4.h"
#include "Shader.h"

namespace Graphos
{
	namespace Graphics
	{
		struct GlShader : Shader
		{
		public:
			unsigned int		vertexShaderID;
			unsigned int		fragmentShaderID;
			unsigned int		programID;

								GlShader( void )
									: vertexShaderID( 0 ), fragmentShaderID( 0 ), programID( 0 ) { }
								GlShader( unsigned int vertex, unsigned int fragment, unsigned int program )
									: vertexShaderID( vertex ), fragmentShaderID( fragment ), programID( program ) { }

			GlShader&			Initialize( std::string vertexBody, std::string fragmentBody );

			void				Use( void ) const;
			bool				SetUniform( std::string name, int value ) const;
			bool				SetUniform( std::string name, float value ) const;
			bool				SetUniform( std::string name, Math::Matrix4 value ) const;

		private:
			std::unordered_map<std::string, unsigned int>
								uniforms;

			void				ScanForVars( std::string vertexBody );
			void				Compile( std::string vertexBody, std::string fragmentBody );
		};
	}
}

#endif//__GL_SHADER