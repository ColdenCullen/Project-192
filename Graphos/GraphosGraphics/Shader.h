#ifndef __SHADER
#define __SHADER

#include <unordered_map>
#include <string>
#include <Gl/GLIncludes.h>
#include "Matrix4.h"

namespace Graphos
{
	namespace Graphics
	{
		struct Shader
		{
		public:
			unsigned int		vertexShaderID;
			unsigned int		fragmentShaderID;
			unsigned int		programID;

								Shader( void )
									: vertexShaderID( 0 ), fragmentShaderID( 0 ), programID( 0 ) { }
								Shader( unsigned int vertex, unsigned int fragment, unsigned int program )
									: vertexShaderID( vertex ), fragmentShaderID( fragment ), programID( program ) { }

			void				Initialize( std::string text );

			void				Use( void ) const;
			bool				SetUniform( std::string name, int value ) const;
			bool				SetUniform( std::string name, float value ) const;
			bool				SetUniform( std::string name, Graphos::Math::Matrix4 value ) const;

		private:
			std::unordered_map<std::string, unsigned int>
								uniforms;
		};
	}
}

#endif//__SHADER