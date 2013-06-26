#ifndef __SHADER_CONTROLLER
#define __SHADER_CONTROLLER

// Includes
#include <unordered_map>
#include <string>

#include "Shader.h"

namespace Graphos
{
	namespace Graphics
	{
		class ShaderController
		{
		public:
			void				Initialize();
			Shader&				GetShader( std::string shaderName );

			template<typename T>
			void				SetAllShadersUniform( std::string uniformName, T value )
			{
				for( auto shader = begin( shaders ); shader != end( shaders ); ++shader )
					shader->second.SetUniform( uniformName, value );
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

			void				AddShader( std::string path, std::string name );

			std::unordered_map<std::string, Shader>
								shaders;
		};
	}
}

#endif//__SHADER_CONTROLLER