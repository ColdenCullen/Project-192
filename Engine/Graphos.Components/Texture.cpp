#include "Texture.h"

#include <GL/GLIncludes.h>
#include <FreeImage.h>
#include "IShader.h"

using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Graphics;

void Texture::LoadFromFile( std::string filePath )
{
	// Load and convert to 32 bits
	FIBITMAP* imageData = FreeImage_ConvertTo32Bits( FreeImage_Load( FreeImage_GetFileType( filePath.c_str() ), filePath.c_str() ) );

	// Get dimensions
	width = FreeImage_GetWidth( imageData );
	height = FreeImage_GetHeight( imageData );

	// Buffer to GL
	glGenTextures( 1, &textureID );
	glBindTexture( GL_TEXTURE_2D, textureID );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA ,GL_UNSIGNED_BYTE, (GLvoid*)FreeImage_GetBits( imageData ) );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

	//if( glGetError() )
	//	throw exception( "Failed to buffer texture." );

	//gluErrorString( glGetError() );

	FreeImage_Unload( imageData );

	glBindTexture( GL_TEXTURE_2D, NULL );
}

void Texture::Draw( IShader* shader )
{
	
	shader->BindTexture( *this );
}

void Texture::Shutdown( void )
{
	glBindTexture( GL_TEXTURE_2D, NULL );
	glDeleteBuffers( 1, &textureID );
}