#ifndef __SHADER
#define __SHADER

#include <string>
#include <vector>
#include "GraphosBehavior.h"
#include "Matrix4.h"
#include "ShaderController.h"

namespace Graphos
{
	namespace Core
	{
		class Mesh;
		class Texture;
	}

	namespace Graphics
	{
		struct ConstBuffer
		{
			std::unordered_map<std::string, std::pair<gSize, gSize>> meta;
			gSize				 totalSize;

			ConstBuffer() { totalSize = 0; }

			void AddProperty( std::string name, gSize size )
			{
				meta[ name ] = std::pair<gSize, gSize>( totalSize, size );
				totalSize += size;
			}
		};

		class IShader
		{
		public:
								IShader( void );

			virtual void		Shutdown( void );
			virtual void		Draw( Core::Mesh& mesh ) const;
			virtual void		BindTexture( Core::Texture& text) const;

			virtual void		RegisterConstBuffer( std::string name, ConstBuffer* buf );
			
			virtual void		SetUniform( std::string name, const gFloat value ) const;
			virtual void		SetUniform( std::string name, const gInt value ) const;
								
								/**
								 * @param name Name of the uniform
								 * @param value The data
								 * @param size The number of values in data
								 */
			virtual void		SetUniformArray( std::string name, const gFloat* value, const gInt size ) const;
			virtual void		SetUniformArray( std::string name, const gInt* value, const gInt size ) const;

								/**
								 * @param name Name of the uniform
								 * @param value The data
								 * @param size The size (in bytes) of value
								 */
			virtual void		SetUniformBuffer( std::string name, const gByte* value, const size_t size ) const;
			virtual void		SetUniformMatrix( std::string name, const Math::Matrix4& matrix ) const;

			void				SetModelMatrix( const Math::Matrix4& value );
			void				SetViewMatrix( const Math::Matrix4& value );
			void				SetProjectionMatrix( const Math::Matrix4& value );

			Math::Matrix4*		GetModelMatrix( void ) { return modelMatrix; }
			Math::Matrix4*		GetViewMatrix( void ) { return viewMatrix; }
			Math::Matrix4*		GetProjectionMatrix( void ) { return projectionMatrix; }
			Math::Matrix4*		GetModelViewProjectionMatrix( void ) { return modelViewProjection; }

		protected:
			Math::Matrix4*		modelMatrix;
			Math::Matrix4*		viewMatrix;
			Math::Matrix4*		projectionMatrix;
			Math::Matrix4*		modelViewProjection;

			Core::GraphosBehavior* script;

		private:
			void				UpdateMVPMatrix( void );

			friend class		ShaderController;
		};
	}
}

#endif//__SHADER
