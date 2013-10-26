#ifndef __SHADER_CONTROLLER
#define __SHADER_CONTROLLER

// Includes
#include <unordered_map>
#include <string>

#include "IShader.h"
#include "IController.h"
#include "ISingleton.h"

namespace Graphos
{
	namespace Graphics
	{
		class ShaderController : public Core::IController
		{
		public:
			const std::string	ShaderPath;

			void				Initialize( void ) override;
			void				Shutdown( void ) override;
			IShader*			GetShader( std::string shaderName );

			template<typename T>
			void				SetAllShadersUniform( std::string uniformName, T value )
			{
				//for( auto shader : shaders )
					//shader.second->SetUniform( uniformName, value );
			}

		private:
								ShaderController( void ) : ShaderPath( "Resources\\Shaders\\" ) { }
								ShaderController( const ShaderController& ) : ShaderPath( "Resources\\Shaders\\" ) { }
			void				operator=( const ShaderController& );

			std::unordered_map<std::string, IShader*>
								shaders;

			friend class		Core::ISingleton<ShaderController>;
		};
	}
}

#endif//__SHADER_CONTROLLER