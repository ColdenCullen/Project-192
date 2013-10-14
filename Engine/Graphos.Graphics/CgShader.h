#ifndef __CG_SHADER
#define __CG_SHADER

#include "IShader.h"

#include <string>
#include <Cg/cg.h>

namespace DirectX
{
	struct ID3D11InputLayout;
}

namespace Graphos
{
	namespace Graphics
	{
		class CgShader : public IShader
		{
		public:
								CgShader( std::string vertexPath, std::string fragmentPath );

			static void			InitCg( void );
			static void			ShutdownCg( void );
			void				Shutdown( void ) override;

			void				Draw( const Core::Mesh& mesh ) const override;
			void				BindTexture( const Core::Texture& text ) const override;

			void				SetUniform( std::string name, int value ) const override;
			void				SetUniform( std::string name, float value ) const override;
			void				SetUniform( std::string name, const Math::Matrix4& value ) const;// override;


		private:
			static CGcontext	cgContext;

			// For Programs
			static CGprofile	cgVertexProfile;
			static CGprofile	cgFragmentProfile;
			CGprogram			cgVertexProgram;
			CGprogram			cgFragmentProgram;

			DirectX::ID3D11InputLayout*  vertexLayout;
		};
	}
}

#endif//__CG_SHADER