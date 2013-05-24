#ifndef _AWESOMIUM_H_
#define _AWESOMIUM_H_

#include <GL/glincludes.h>

#include <Awesomium/WebView.h>
#include <Awesomium/BitmapSurface.h>

#include <string>

#include "Ingredient.h"

using namespace Awesomium;

namespace Graphos
{
	namespace Content
	{
		class AwesomiumView : public Ingredient
		{
		public:
								AwesomiumView( void ) : webView( nullptr ), surface( nullptr ), buffer( nullptr ) { }
								AwesomiumView( std::string url, unsigned int width, unsigned int height ) { Initialize( url, width, height ); }
								~AwesomiumView( void ) { }

			bool				Initialize( std::string url, unsigned int width, unsigned int height );
			bool				Update( float deltaTime );
			void				Draw( void );
			void				Shutdown( void );

			unsigned int		textureID;

			friend class		UserInterface;

		//private:
			WebView*			webView;
			BitmapSurface*		surface;

			unsigned char*		buffer;
		};
	}
}

#endif//_AWESOMIUM_H_