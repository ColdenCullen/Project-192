#ifndef __DXSHADER
#define __DXSHADER

#include <string>
#include "IShader.h"


namespace Graphos
{
	namespace Graphics
	{

		class DXShader : public IShader
		{
			public:
								DXShader(void);
								~DXShader(void);
			DXShader&			Initialize( std::string vertexPath, std::string fragmentPath );
			void				Shutdown( void ) override;
			void				Draw( const Core::Mesh& mesh ) const override;
			void				BindTexture( const Core::Texture& text ) const override;

			
		};
	}
}

#endif//__DXSHADER
