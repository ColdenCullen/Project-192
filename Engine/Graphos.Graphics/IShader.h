#ifndef __SHADER
#define __SHADER

#include "Matrix4.h"
#include <string>
#include <v8/v8.h>

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
			virtual void		Shutdown( void );
			virtual void		Draw( const Core::Mesh& mesh ) const;
			virtual void		BindTexture( const Core::Texture& text) const;

			virtual void		BuildConstBuffer( v8::Arguments args );
			
			virtual void		SetUniform( std::string name, const float value, ShaderType type ) const;
			virtual void		SetUniform( std::string name, const int value, ShaderType type ) const;
			virtual void		SetUniformArray( std::string name, const float* value, const int size, ShaderType type ) const;
			virtual void		SetUniformArray( std::string name, const int* value, const int size, ShaderType type ) const;

			void				SetModelMatrix( const Math::Matrix4& value );
			void				SetViewMatrix( const Math::Matrix4& value );
			void				SetProjectionMatrix( const Math::Matrix4& value );

		protected:
			Math::Matrix4		modelMatrix;
			Math::Matrix4		viewMatrix;
			Math::Matrix4		projectionMatrix;
			Math::Matrix4		modelViewProjection;

		private:
			void				UpdateMVPMatrix( void );
		};
	}
}

#endif//__SHADER