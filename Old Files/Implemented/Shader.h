#ifndef _SHADER_H_
#define _SHADER_H_

#include <unordered_map>
#include <string>
#include <Gl/GLIncludes.h>
#include "Matrix.h"

using namespace std;

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

			void				Initialize( string text );

			void				Use( void ) const;
			bool				SetUniform( string name, int value ) const;
			bool				SetUniform( string name, float value ) const;
			bool				SetUniform( string name, Graphos::Math::Matrix value ) const;

		private:
			unordered_map<string, unsigned int>
								uniforms;
		};
	}
}

#endif//_SHADER_H_