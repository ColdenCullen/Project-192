

#include <GL\GLIncludes.h>
#include <FreeImage.h>
#include "IShader.h"
#include "Config.h"
#include "GraphicsController.h"
#include <DirectX\DirectXTex.h>

#include "Texture.h"

using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Graphics;
using namespace DirectX;

void Texture::LoadFromFile( string filePath )
{
	if( ISingleton<GraphicsController>::Get().GetActiveAdapter() == GraphicsAdapter::OpenGL )
	{
		// Load and convert to 32 bits
		FIBITMAP* imageData = FreeImage_ConvertTo32Bits( FreeImage_Load( FreeImage_GetFileType( filePath.c_str() ), filePath.c_str() ) );

		// Get dimensions
		width = FreeImage_GetWidth( imageData );
		height = FreeImage_GetHeight( imageData );

		// Buffer to GL
		glGenTextures( 1, &glTextureId );
		glBindTexture( GL_TEXTURE_2D, glTextureId );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA ,GL_UNSIGNED_BYTE, (GLvoid*)FreeImage_GetBits( imageData ) );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

		FreeImage_Unload( imageData );

		glBindTexture( GL_TEXTURE_2D, NULL );
	}
#if defined( _WIN32 )
	else if( ISingleton<GraphicsController>::Get().GetActiveAdapter() == GraphicsAdapter::DirectX )
	{
		wstring wFilePath( filePath.begin(), filePath.end() );

		TexMetadata metaData;
		GetMetadataFromWICFile( wFilePath.c_str(), NULL, metaData );

		ScratchImage scratchImg;
		LoadFromWICFile( wFilePath.c_str(), WIC_FLAGS_NONE, &metaData, scratchImg );

		const Image* img = scratchImg.GetImage( 0, 0, 0 );
		//CreateTexture( device, img, 1, metaData, &dxTexture );
	}
#endif//_WIN32
}

void Texture::Draw( IShader* shader )
{
	shader->BindTexture( *this );
}

void Texture::Shutdown( void )
{
	if( ISingleton<GraphicsController>::Get().GetActiveAdapter() == GraphicsAdapter::OpenGL )
	{
		glBindTexture( GL_TEXTURE_2D, NULL );
		glDeleteBuffers( 1, &glTextureId );
	}
#if defined( _WIN32 )
	else if( ISingleton<GraphicsController>::Get().GetActiveAdapter() == GraphicsAdapter::DirectX )
	{
		ReleaseCOMobjMacro( dxTexture );
	}
#endif//_WIN32
}