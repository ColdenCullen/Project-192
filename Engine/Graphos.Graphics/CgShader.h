#ifndef __CG_SHADER
#define __CG_SHADER

#include "Shader.h"

#include <string>
#include <Cg\cg.h>


namespace Graphos
{
	namespace Graphics
	{
		class CgShader : Shader
		{
		public:
			CgShader&			Initialize( std::string filePath );

		private:
			CGcontext			cgContext;
			CGprogram			cgProgram;
			CGprofile			cgVertexProfile;

			CGparameter			position, color, modelViewMatrix, wave;

			void				InitializeForGl( std::string filePath );
			void				InitializeForDx( std::string filePath );
		};
	}
}

#endif//__CG_SHADER