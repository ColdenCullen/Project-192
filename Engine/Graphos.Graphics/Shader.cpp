#include "stdafx.h"
#include "Shader.h"

#define MIN(x,y) (x < y ? x : y)

using namespace std;
using namespace Graphos::Math;
using namespace Graphos::Graphics;

void Shader::Initialize( string text )
{
	// Init uniform values
	int currentLocation = text.find( "uniform " );

	while( currentLocation != string::npos )
	{
		int start = text.find( " ", currentLocation + 8 ) + 1;
		string uniformName = text.substr( start, MIN( text.find( ";", start + 1 ), text.find( " ", start + 1 ) ) - start );

		uniforms[ uniformName ] = glGetUniformLocation( programID, uniformName.c_str() );

		currentLocation = text.find( "uniform ", start );
	}

	// Init in values
	currentLocation = text.find( "in " );
	int counter = 0;

	while( currentLocation != string::npos )
	{
		int start = text.find( " ", currentLocation + 3 ) + 1;
 		string inName = text.substr( start, MIN( text.find( ";", start + 1 ), text.find( " ", start + 1 ) ) - start );

		glBindAttribLocation( programID, counter, inName.c_str() );

		currentLocation = text.find( "in ", start );

		++counter;
	}
}


void Shader::Use( void ) const
{
	glUseProgram( programID );
}

bool Shader::SetUniform( string name, int value ) const
{
	auto currentUniform = uniforms.find( name );

	if( currentUniform != end( uniforms ) && currentUniform->second != -1 )
		glUniform1i( currentUniform->second, value );
	else
		return false;

	return true;
}

bool Shader::SetUniform( string name, float value ) const
{
	auto currentUniform = uniforms.find( name );

	if( currentUniform != end( uniforms ) && currentUniform->second != -1 )
		glUniform1f( currentUniform->second, value );
	else
		return false;

	return true;
}

bool Shader::SetUniform( string name, Matrix4 value ) const
{
	auto currentUniform = uniforms.find( name );

	if( currentUniform != end( uniforms ) && currentUniform->second != -1 )
		glUniformMatrix4fv( currentUniform->second, 1, false, value.dataArray );
	else
		return false;

	return true;
}