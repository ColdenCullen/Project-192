#include "stdafx.h"
#include "GlShader.h"
#include "File.h"
#include "Mesh.h"
#include "Texture.h"

#define MIN(x,y) (x < y ? x : y)

using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Graphics;
using namespace OpenGL;

GlShader::GlShader( std::string vertexPath, std::string fragmentPath )
	: vertexShaderID( 0 ), fragmentShaderID( 0 ), programID( 0 )
{

	string vertexBody = File::ReadFile( vertexPath );
	string fragmentBody = File::ReadFile( fragmentPath );
	Compile( vertexBody, fragmentBody );
	ScanForVars( vertexBody );
}

void GlShader::ScanForVars( string vertexBody )
{
	// Init uniform values
	int currentLocation = vertexBody.find( "uniform " );

	while( currentLocation != string::npos )
	{
		int start = vertexBody.find( " ", currentLocation + 8 ) + 1;
		string uniformName = vertexBody.substr( start, MIN( vertexBody.find( ";", start + 1 ), vertexBody.find( " ", start + 1 ) ) - start );

		uniforms[ uniformName ] = glGetUniformLocation( programID, uniformName.c_str() );

		currentLocation = vertexBody.find( "uniform ", start );
	}

	// Init in values
	currentLocation = vertexBody.find( "in " );
	int counter = 0;

	while( currentLocation != string::npos )
	{
		int start = vertexBody.find( " ", currentLocation + 3 ) + 1;
		string inName = vertexBody.substr( start, MIN( vertexBody.find( ";", start + 1 ), vertexBody.find( " ", start + 1 ) ) - start );

		glBindAttribLocation( programID, counter, inName.c_str() );

		currentLocation = vertexBody.find( "in ", start );

		++counter;
	}
}

void GlShader::Compile( string vertexBody, string fragmentBody )
{
	// Create shader
	vertexShaderID = glCreateShader( GL_VERTEX_SHADER );
	fragmentShaderID = glCreateShader( GL_FRAGMENT_SHADER );
	programID = glCreateProgram();

	// Load the source
	GLint vertexShaderLength = vertexBody.size();
	GLint fragmentShaderLength = fragmentBody.size();
	const char* vertexShaderCString = vertexBody.c_str();
	const char* fragmentShaderCString = fragmentBody.c_str();

	glShaderSource( vertexShaderID, 1, &vertexShaderCString, &vertexShaderLength );
	glShaderSource( fragmentShaderID, 1, &fragmentShaderCString, &fragmentShaderLength );

	// Compile shaders, check for errors
	GLint compileStatus = GL_TRUE;

	glCompileShader( vertexShaderID );
	glGetShaderiv( vertexShaderID, GL_COMPILE_STATUS, &compileStatus );
	if( compileStatus != GL_TRUE )
	{
		throw exception( "Error compiling vertex shader." );
	}

	glCompileShader( fragmentShaderID );
	glGetShaderiv( fragmentShaderID, GL_COMPILE_STATUS, &compileStatus );
	if( compileStatus != GL_TRUE )
	{
		throw exception( "Error compiling fragment shader." );
	}

	// Attach shaders to program
	glAttachShader( programID, vertexShaderID );
	glAttachShader( programID, fragmentShaderID );

	// Link everything
	glLinkProgram( programID );

	// Check completeness
	glGetProgramiv( programID, GL_LINK_STATUS, &compileStatus );
	if( compileStatus != GL_TRUE )
		throw exception( "Error linking shader program." );
}

void GlShader::Draw( Mesh& mesh ) const
{
	SetUniformArray( "modelViewProjection", modelViewProjection.dataArray, 16, ShaderType::VERTEX );

	glUseProgram( programID );

	glBindVertexArray( mesh.GetGlVao() );
	//glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mesh.GetIndexBuffer() );

	// Draw
	glDrawElements( GL_TRIANGLES, mesh.GetNumVertices(), GL_UNSIGNED_INT, 0 );
}

void GlShader::BindTexture( Texture& text ) const
{
	glBindTexture( GL_TEXTURE_2D, text.GetTextureId().gl );
}
