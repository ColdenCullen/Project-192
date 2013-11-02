#ifndef __SHADER
#define __SHADER

#include "Matrix4.h"
#include <string>

namespace Graphos
{
	namespace Core
	{
		class Mesh;
		class Texture;
	}

	namespace Graphics
	{
		enum class ShaderType { VERTEX, FRAGMENT };

		class IShader
		{
		public:
			virtual void		Shutdown( void ) = 0;
			virtual void		Draw( Core::Mesh& mesh ) const = 0;
			virtual void		BindTexture( Core::Texture& text) const = 0;
			
			virtual void		SetUniform( std::string name, const float value, ShaderType type ) const = 0;
			virtual void		SetUniform( std::string name, const int value, ShaderType type ) const = 0;
			virtual void		SetUniformArray( std::string name, const float* value, const int size, ShaderType type ) const = 0;
			virtual void		SetUniformArray( std::string name, const int* value, const int size, ShaderType type ) const = 0;

			void				SetModelMatrix( const Math::Matrix4& value ) { modelMatrix = value; UpdateMVPMatrix(); }
			void				SetViewMatrix( const Math::Matrix4& value ) { viewMatrix = value; UpdateMVPMatrix(); }
			void				SetProjectionMatrix( const Math::Matrix4& value ) { projectionMatrix = value; UpdateMVPMatrix(); }

		protected:
			Math::Matrix4		modelMatrix;
			Math::Matrix4		viewMatrix;
			Math::Matrix4		projectionMatrix;
			Math::Matrix4		modelViewProjection;

		private:
			void				UpdateMVPMatrix( void ) { modelViewProjection = modelMatrix * viewMatrix * projectionMatrix; }
		};
	}
}

#endif//__SHADER