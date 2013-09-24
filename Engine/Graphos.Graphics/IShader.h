#ifndef __SHADER
#define __SHADER

#include "Matrix4.h"

namespace Graphos
{
	namespace Core
	{
		class Mesh;
		class Texture;
	}

	namespace Graphics
	{
		class IShader
		{
		public:
			virtual void		Draw( const Core::Mesh& mesh ) const = 0;
			virtual void		BindTexture( const Core::Texture& text) const = 0;

			virtual void		SetUniform( std::string name, int value ) const = 0;
			virtual void		SetUniform( std::string name, float value ) const = 0;
			virtual void		SetUniform( std::string name, const Math::Matrix4& value ) const = 0;

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