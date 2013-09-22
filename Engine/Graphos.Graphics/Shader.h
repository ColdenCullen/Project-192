#ifndef __SHADER
#define __SHADER

#include "Matrix4.h"

namespace Graphos
{
	namespace Core
	{
		class Mesh;
	}

	namespace Graphics
	{
		class Shader
		{
		public:
			virtual void		Draw( const Core::Mesh& mesh ) const = 0;

			virtual void		SetUniform( std::string name, int value ) const = 0;
			virtual void		SetUniform( std::string name, float value ) const = 0;
			virtual void		SetUniform( std::string name, const Math::Matrix4& value ) const = 0;
		};
	}
}

#endif//__SHADER