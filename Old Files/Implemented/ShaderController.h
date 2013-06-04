#ifndef _SHADER_CONTROLLER_H_
#define _SHADER_CONTROLLER_H_

// Includes
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

#if defined( _WIN32 )
 #include <windirent.h>
#elif defined( __APPLE__ )
 #include <dirent.h>
#endif

#include "WindowController.h"
#include "Shader.h"

using namespace std;

namespace Graphos
{
	namespace Graphics
	{
		class ShaderController
		{
		public:
			bool				Initialize();
			Shader&				GetShader( string shaderName );

			template<typename T>
			void				SetAllShadersUniform( string uniformName, T value )
			{
				for_each(
					begin( shaders ),
					end( shaders ),
					[&]( pair<string, Shader> shader )
					{
						shader.second.SetUniform( uniformName, value );
					}
				);
			}

			static
			ShaderController&	Get( void )
			{
				static ShaderController instance;
				return instance;
			}

		private:
								ShaderController( void ) { }
								ShaderController( const ShaderController& );
			void				operator=( const ShaderController& );

			bool				AddShader( string path, string name );

			unordered_map<string, Shader>
								shaders;
		};
	}
}

#endif//_SHADER_CONTROLLER_H_