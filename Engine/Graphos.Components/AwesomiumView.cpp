#include "AwesomiumView.h"

#include <Awesomium\WebCore.h>
#include <Awesomium\STLHelpers.h>
#include "IShader.h"
#include "GraphicsController.h"
#include "AdapterController.h"

#include <GL\GLIncludes.h>
using namespace OpenGL;
#include <DirectX\DirectXIncludes.h>
using namespace DirectX;

using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Graphics;
using namespace Graphos::Math;
using namespace Awesomium;

bool AwesomiumView::Initialize( string url, unsigned int width, unsigned int height )
{
	// Generate a texture to use
	glGenTextures( 1, &textureId.gl );

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
	if( GraphicsController::GetActiveAdapter() == GraphicsAdapter::OpenGL )
		buffer.gl = new unsigned char[ width * height * 4 ];
#if defined( _WIN32 )
	else if( GraphicsController::GetActiveAdapter() == GraphicsAdapter::DirectX )
	{
		D3D11_TEXTURE2D_DESC textureDesc;
		ZeroMemory(&textureDesc, sizeof(D3D11_TEXTURE2D_DESC));
		textureDesc.ArraySize = 1;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		textureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		textureDesc.MipLevels = 1;
		textureDesc.MiscFlags = 0;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage = D3D11_USAGE_DYNAMIC;
		textureDesc.Width = width;
		textureDesc.Height = height;

		AdapterController::Get()->GetDevice().dx->CreateTexture2D( &textureDesc, NULL, &buffer.dx );
		AdapterController::Get()->GetDevice().dx->CreateShaderResourceView( buffer.dx, NULL, &textureId.dx );

	}
#endif

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
		shader->BindTexture( *this );

		if( surface && surface->is_dirty() )
		{
			// Copy to buffer
			BufferAwesomiumSurface();
		}
	}
}

void AwesomiumView::BufferAwesomiumSurface( void )
{
	if( GraphicsController::GetActiveAdapter() == GraphicsAdapter::OpenGL )
	{
		surface->CopyTo( buffer.gl, surface->row_span(), 4, false, true );

		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, surface->width(), surface->height(), 0, GL_BGRA ,GL_UNSIGNED_BYTE, (GLvoid*)buffer.gl );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	}
#if defined( _WIN32 )
	else if( GraphicsController::GetActiveAdapter() == GraphicsAdapter::DirectX )
	{
		D3D11_MAPPED_SUBRESOURCE subresource;
		
		ID3D11DeviceContext* temp = AdapterController::Get()->GetDeviceContext().dx;
		temp->Map( buffer.dx, 0, D3D11_MAP_WRITE_DISCARD, 0, &subresource );
		surface->CopyTo( (byte*)subresource.pData, surface->row_span(), 4, false, false );
		temp->Unmap( buffer.dx, 0 );

		ReleaseCOMobjMacro( textureId.dx );
		AdapterController::Get()->GetDevice().dx->CreateShaderResourceView( buffer.dx, NULL, &textureId.dx );

	}
#endif//_WIN32
}

void AwesomiumView::Shutdown( void )
{
	// KILL EVERYTHING
	webView->Destroy();
	//WebCore::Shutdown();
	if( GraphicsController::GetActiveAdapter() == GraphicsAdapter::OpenGL )
		delete [] buffer.gl;
#if defined( _WIN32 )
	else if( GraphicsController::GetActiveAdapter() == GraphicsAdapter::DirectX )
	{
		ReleaseCOMobjMacro( textureId.dx );
		ReleaseCOMobjMacro( buffer.dx );
	}
#endif

}