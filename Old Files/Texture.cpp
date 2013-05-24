#include "Texture.h"

using namespace Graphos::Content;

bool Texture::LoadFromFile( std::string filePath )
{
	// Load and convert to 32 bits
	FIBITMAP* imageData = FreeImage_ConvertTo32Bits( FreeImage_Load( FreeImage_GetFileType( filePath.c_str(), 0 ), filePath.c_str() ) );

	// Get dimensions
	width = FreeImage_GetWidth( imageData );
	height = FreeImage_GetHeight( imageData );

	// Buffer to GL
	glGenTextures( 1, &textureID );
	glBindTexture( GL_TEXTURE_2D, textureID );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA ,GL_UNSIGNED_BYTE, (GLvoid*)FreeImage_GetBits( imageData ) );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

	if( glGetError() )
		return false;

	FreeImage_Unload( imageData );

	glBindTexture( GL_TEXTURE_2D, NULL );

	return true;
}

void Texture::Draw( void )
{
	glBindTexture( GL_TEXTURE_2D, textureID );
}

void Texture::Shutdown( void )
{
	glBindTexture( GL_TEXTURE_2D, NULL );
	glDeleteBuffers( 1, &textureID );
}