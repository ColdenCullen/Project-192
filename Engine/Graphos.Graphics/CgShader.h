#ifndef __CG_SHADER
#define __CG_SHADER

#include "Shader.h"

#include <string>
#include <Cg\cg.h>

namespace Graphos
{
	namespace Graphics
	{
		class CgShader : public Shader
		{
		public:
			CgShader&			Initialize( std::string filePath );

			void				Use( void ) const override;
			void				SetUniform( std::string name, int value ) const override;
			void				SetUniform( std::string name, float value ) const override;
			void				SetUniform( std::string name, const Math::Matrix4& value ) const override;

		private:
			static
			CGcontext			cgContext;
			CGeffect			cgEffect;
			CGtechnique			cgTechnique;

			CGparameter			modelViewMatrix;

			void				InitializeForGl( std::string filePath );
			void				InitializeForDx( std::string filePath );
		};
	}
}

#endif//__CG_SHADER