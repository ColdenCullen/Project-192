#include "stdafx.h"
#include "GlShader.h"
#include "File.h"
#include "Mesh.h"

#define MIN(x,y) (x < y ? x : y)

using namespace std;
using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Graphics;

GlShader& GlShader::Initialize( string vertexPath, string fragmentPath )
{
	string vertexBody = File::ReadFile( vertexPath );
	string fragmentBody = File::ReadFile( fragmentPath );
	Compile( vertexBody, fragmentBody );
	ScanForVars( vertexBody );
	return *this;
}

void GlShader::SetUniform( string name, int value ) const
{
	auto currentUniform = uniforms.find( name );

	if( currentUniform != end( uniforms ) && currentUniform->second != -1 )
		glUniform1i( currentUniform->second, value );
}

void GlShader::SetUniform( string name, float value ) const
{
	auto currentUniform = uniforms.find( name );

	if( currentUniform != end( uniforms ) && currentUniform->second != -1 )
		glUniform1f( currentUniform->second, value );
}

void GlShader::SetUniform( string name, const Matrix4& value ) const
{
	auto currentUniform = uniforms.find( name );

	if( currentUniform != end( uniforms ) && currentUniform->second != -1 )
		glUniformMatrix4fv( currentUniform->second, 1, false, value.dataArray );
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

void GlShader::Draw( const Mesh& mesh ) const 
{
	glUseProgram( programID );

	glBindVertexArray( mesh.GetVAO() );
	//glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mesh.GetIndexBuffer() );

	// Draw
	glDrawElements( GL_TRIANGLES, mesh.GetNumElements(), GL_UNSIGNED_INT, 0 );
}