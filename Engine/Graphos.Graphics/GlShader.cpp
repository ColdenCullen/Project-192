#include "stdafx.h"
#include "GlShader.h"
#include "File.h"
#include "Mesh.h"
#include "Texture.h"
#include "OutputController.h"

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
	ScanForVars( vertexBody, fragmentBody );
}

void GlShader::ScanForVars( string vertexBody, string fragmentBody )
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

	// Init uniform values
	currentLocation = fragmentBody.find( "uniform " );

	while( currentLocation != string::npos )
	{
		int start = fragmentBody.find( " ", currentLocation + 8 ) + 1;
		string uniformName = fragmentBody.substr( start, MIN( fragmentBody.find( ";", start + 1 ), fragmentBody.find( " ", start + 1 ) ) - start );

		uniforms[ uniformName ] = glGetUniformLocation( programID, uniformName.c_str() );

		currentLocation = fragmentBody.find( "uniform ", start );
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
		OutputController::PrintMessage( OutputType::OT_ERROR, "Compilation errors on vertex shader." );

		GLint maxLength = 256;
		glGetShaderiv( vertexShaderID, GL_INFO_LOG_LENGTH, &maxLength );

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog( maxLength );
		glGetShaderInfoLog( vertexShaderID, maxLength, &maxLength, &infoLog[0] );

		OutputController::PrintMessage( OutputType::OT_ERROR, string( "\n" ) + string( &infoLog[0] ) );
	}

	glCompileShader( fragmentShaderID );
	glGetShaderiv( fragmentShaderID, GL_COMPILE_STATUS, &compileStatus );
	if( compileStatus != GL_TRUE )
	{
		OutputController::PrintMessage( OutputType::OT_ERROR, "Compilation errors on fragment shader." );

		GLint maxLength = 256;
		glGetShaderiv( fragmentShaderID, GL_INFO_LOG_LENGTH, &maxLength );

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog( maxLength );
		glGetShaderInfoLog( fragmentShaderID, maxLength, &maxLength, &infoLog[0] );

		OutputController::PrintMessage( OutputType::OT_ERROR, string( "\n" ) + string( &infoLog[0] ) );
	}

	// Attach shaders to program
	glAttachShader( programID, vertexShaderID );
	glAttachShader( programID, fragmentShaderID );

	// Link everything
	glLinkProgram( programID );

	// Check completeness
	glGetProgramiv( programID, GL_LINK_STATUS, &compileStatus );
	if( compileStatus != GL_TRUE )
	{
		OutputController::PrintMessage( OutputType::OT_ERROR, "Error linking shader program." );

		GLint maxLength = 256;
		glGetShaderiv( programID, GL_INFO_LOG_LENGTH, &maxLength );

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog( maxLength );
		glGetProgramInfoLog( programID, maxLength, &maxLength, &infoLog[0] );

		OutputController::PrintMessage( OutputType::OT_ERROR, string( "\n" ) + string( &infoLog[0] ) );
	}
}

void GlShader::Draw( Mesh& mesh ) const
{
	glUseProgram( programID );

	SetUniformArray( "modelViewProjection", modelViewProjection.dataArray, 16, ShaderType::VERTEX );
	SetUniformArray( "modelMatrix", modelMatrix.dataArray, 16, ShaderType::VERTEX );
	SetUniform( "shaderTexture", 0, ShaderType::FRAGMENT );

	glBindVertexArray( mesh.GetGlVao() );
	//glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mesh.GetIndexBuffer() );

	// Draw
	glDrawElements( GL_TRIANGLES, mesh.GetNumVertices(), GL_UNSIGNED_INT, 0 );
}

void GlShader::BindTexture( Texture& text ) const
{
	glBindTexture( GL_TEXTURE_2D, text.GetTextureId().gl );
}

void GlShader::BuildConstBuffer( v8::Arguments args )
{
	// LOL JK
}

void GlShader::SetUniformArray( string name, const int* value, const int size, ShaderType type ) const 
{
	auto currentUniform = uniforms.find( name );

	if( currentUniform != end( uniforms ) && currentUniform->second != -1 )
		glUniform1iv( currentUniform->second, size, value );
}

void GlShader::SetUniformArray( string name, const float* value, const int size, ShaderType type ) const 
{ 
	auto currentUniform = uniforms.find( name );

	if( currentUniform != end( uniforms ) && currentUniform->second != -1 )
		//glUniform1fv( currentUniform->second, size, value );
		glUniformMatrix4fv( currentUniform->second, 1, false, value );
}

void GlShader::SetUniform( string name, const int value, ShaderType type ) const 
{
	auto currentUniform = uniforms.find( name );

	if( currentUniform != end( uniforms ) && currentUniform->second != -1 )
		glUniform1i( currentUniform->second, value );
}

void GlShader::SetUniform( string name, const float value, ShaderType type ) const 
{
	auto currentUniform = uniforms.find( name );

	if( currentUniform != end( uniforms ) && currentUniform->second != -1 )
		glUniform1f( currentUniform->second, value );
}
