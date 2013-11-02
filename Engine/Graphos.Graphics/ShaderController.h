#ifndef __SHADER_CONTROLLER
#define __SHADER_CONTROLLER

// Includes
#include <unordered_map>
#include <string>

namespace Graphos
{
	namespace Graphics
	{
		class IShader;

		class ShaderController
		{
		public:
			static void			Initialize( void );
			static void			Shutdown( void );
			static IShader*		GetShader( std::string shaderName );

			template<typename T>
			static void			SetAllShadersUniform( std::string uniformName, T value )
			{
				//for( auto shader : shaders )
					//shader.second->SetUniform( uniformName, value );
			}

		private:
								ShaderController( void ) { }
								ShaderController( const ShaderController& );
			void				operator=( const ShaderController& );

			static std::unordered_map<std::string, IShader*>
								shaders;
		};
	}
}

#endif//__SHADER_CONTROLLER