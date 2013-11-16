#ifndef __AWESOMIUM_VIEW
#define __AWESOMIUM_VIEW

#include <Awesomium/WebView.h>
#include <Awesomium/BitmapSurface.h>

#include <string>

#include "IComponent.h"
#include "Texture.h"

namespace DirectX
{
	struct ID3D11Texture2D;
}

namespace Graphos
{
	namespace Core
	{
		class AwesomiumView : public Texture
		{
		public:
								AwesomiumView( void ) : webView( nullptr ), surface( nullptr ) { }
								AwesomiumView( std::string url, gUInt width, gUInt height ) { Initialize( url, width, height ); }
								~AwesomiumView( void ) { }

			bool				Initialize( std::string url, gUInt width, gUInt height );
			void				Update( void ) override;
			void				Draw( Graphics::IShader* shader ) override;
			void				Shutdown( void ) override;


			friend class		UserInterface;

		//private:
			Awesomium::WebView*	webView;
			Awesomium::BitmapSurface*
								surface;
			union 
			{
				gByte*						gl;
				DirectX::ID3D11Texture2D*	dx;
			} buffer;

		private:
			void				BufferAwesomiumSurface();
		};
	}
}

#endif//__AWESOMIUM_VIEW