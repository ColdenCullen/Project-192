#ifndef __AWESOMIUM_VIEW
#define __AWESOMIUM_VIEW

#include <Awesomium\WebView.h>
#include <Awesomium\BitmapSurface.h>

#include <string>

#include "IComponent.h"

namespace Awesomium
{
	//class WebView;
	//class BitmapSurface;
}

namespace Graphos
{
	namespace Core
	{
		class AwesomiumView : public IComponent
		{
		public:
								AwesomiumView( void ) : webView( nullptr ), surface( nullptr ), buffer( nullptr ) { }
								AwesomiumView( std::string url, unsigned int width, unsigned int height ) { Initialize( url, width, height ); }
								~AwesomiumView( void ) { }

			bool				Initialize( std::string url, unsigned int width, unsigned int height );
			void				Update( void ) override;
			void				Draw( Graphics::IShader* shader ) override;
			void				Shutdown( void ) override;

			unsigned int		textureID;

			friend class		UserInterface;

		//private:
			Awesomium::WebView*	webView;
			Awesomium::BitmapSurface*
								surface;

			unsigned char*		buffer;
		};
	}
}

#endif//__AWESOMIUM_VIEW