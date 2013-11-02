#include "AwesomiumView.h"

#include <Awesomium\WebCore.h>
//#include <Awesomium\WebView.h>
#include <Awesomium\STLHelpers.h>
#include "IShader.h"
//#include <Awesomium/BitmapSurface.h>

#define NO_NAMESPACE
#include <GL\GLIncludes.h>

using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Graphics;
using namespace Graphos::Math;
using namespace Awesomium;

bool AwesomiumView::Initialize( string url, unsigned int width, unsigned int height )
{
	// Generate a texture to use
	glGenTextures( 1, &textureID );

	if( !WebCore::instance() )
	{
		WebConfig config;

		config.additional_options = WebStringArray( 1 );
		config.additional_options[ 0 ] = WSLit( "--allow-file-access-from-files" );

		// If debugging, allow remote debugging
#ifdef _DEBUG
		config.remote_debugging_port = 1337;
#endif

		WebCore::Initialize( config );
	}

	WebPreferences prefs;
	prefs.allow_file_access_from_file_url = true;

	webView = WebCore::instance()->CreateWebView( width, height, WebCore::instance()->CreateWebSession( WSLit( "" ), prefs ) );
	webView->LoadURL( WebURL( WSLit( url.c_str() ) ) );
	webView->SetTransparent( true );

	// Initialize buffer
	buffer = new unsigned char[ width * height * 4 ];

	return true;
}

void AwesomiumView::Update( void )
{
	if( WebCore::instance() )
	{
		// Update page
		WebCore::instance()->Update();

		// Get the surface
		surface = static_cast<BitmapSurface*>( webView->surface() );
	}
}

void AwesomiumView::Draw( IShader* shader )
{
	if( WebCore::instance() )
	{
		glBindTexture( GL_TEXTURE_2D, textureID );

		if( surface )
		{
			if( surface->is_dirty() )
			{
				// Copy to buffer
				surface->CopyTo( buffer, surface->row_span(), 4, false, true );

				glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, surface->width(), surface->height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)buffer );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
			}
		}
	}
}

void AwesomiumView::Shutdown( void )
{
	// KILL EVERYTHING
	webView->Destroy();
	//WebCore::Shutdown();
	delete[] buffer;
}