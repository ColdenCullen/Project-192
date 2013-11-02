#include "GraphicsController.h"
#include "IShader.h"

#include <DirectX/DirectXTex.h>
#include "Texture.h"

#include <GL/GLIncludes.h>
using namespace OpenGL;
#include <FreeImage.h>

#include "AdapterController.h"

using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Graphics;

void Texture::LoadFromFile( string filePath )
{
	if( GraphicsController::GetActiveAdapter() == GraphicsAdapter::OpenGL )
	{
		// Load and convert to 32 bits
		FIBITMAP* imageData = FreeImage_ConvertTo32Bits( FreeImage_Load( FreeImage_GetFileType( filePath.c_str() ), filePath.c_str() ) );

		// Get dimensions
		width = FreeImage_GetWidth( imageData );
		height = FreeImage_GetHeight( imageData );

		// Buffer to GL
		glGenTextures( 1, &textureId.gl );
		glBindTexture( GL_TEXTURE_2D, textureId.gl );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA ,GL_UNSIGNED_BYTE, (GLvoid*)FreeImage_GetBits( imageData ) );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

		FreeImage_Unload( imageData );

		glBindTexture( GL_TEXTURE_2D, NULL );
	}
#if defined( _WIN32 )
	else if( GraphicsController::GetActiveAdapter() == GraphicsAdapter::DirectX )
	{
		wstring wFilePath( filePath.begin(), filePath.end() );

		DirectX::TexMetadata metaData;
		GetMetadataFromWICFile( wFilePath.c_str(), NULL, metaData );

		DirectX::ScratchImage scratchImg;
		LoadFromWICFile( wFilePath.c_str(), DirectX::WIC_FLAGS_NONE, &metaData, scratchImg );

		const DirectX::Image* img = scratchImg.GetImage( 0, 0, 0 );
		auto tempDevice = AdapterController::Get()->GetDevice().dxDevice;
		ID3D11Resource* tex;
		HRESULT result = CreateTexture( reinterpret_cast<ID3D11Device*>(tempDevice), img, 1, metaData, &tex );
		ID3D11ShaderResourceView* srv;
		reinterpret_cast<ID3D11Device*>(tempDevice)->CreateShaderResourceView(tex, NULL, &srv);
		textureId.dx = reinterpret_cast<DirectX::ID3D11ShaderResourceView*>(srv);

	}
#endif//_WIN32
}

void Texture::Draw( IShader* shader )
{
	shader->BindTexture( *this );
}

void Texture::Shutdown( void )
{
	if( GraphicsController::GetActiveAdapter() == GraphicsAdapter::OpenGL )
	{
		glBindTexture( GL_TEXTURE_2D, NULL );
		glDeleteBuffers( 1, &textureId.gl );
	}
#if defined( _WIN32 )
	else if( GraphicsController::GetActiveAdapter() == GraphicsAdapter::DirectX )
	{
	//#define CHANGE_TYPE(type, value) static_cast<type>( static_cast<void*>( value ) )	
		if( textureId.dx )
		{
			reinterpret_cast<ID3D11Resource*>(textureId.dx)->Release();
			textureId.dx = nullptr;
		}
		//ReleaseCOMobjMacro( dxTexture );

	}
#endif//_WIN32
}
