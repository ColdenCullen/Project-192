#include "IShader.h"

using namespace std;
using namespace v8;
using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Graphics;

void IShader::Shutdown( void )
{
	throw exception( "Not implemented" );
}

void IShader::Draw( Mesh& mesh ) const
{
	throw exception( "Not implemented" );
}

void IShader::BindTexture( Texture& text ) const
{
	throw exception( "Not implemented" );
}

void IShader::BuildConstBuffer( Arguments args )
{
	throw exception( "Not implemented" );
}

void IShader::SetUniform( string name, const float value, ShaderType type ) const
{
	throw exception( "Not implemented" );
}

void IShader::SetUniform( string name, const int value, ShaderType type ) const
{
	throw exception( "Not implemented" );
}

void IShader::SetUniformArray( string name, const float* value, const int size, ShaderType type ) const
{
	throw exception( "Not implemented" );
}

void IShader::SetUniformArray( string name, const int* value, const int size, ShaderType type ) const
{
	throw exception( "Not implemented." );
}

void IShader::UpdateMVPMatrix( void )
{
	modelViewProjection = modelMatrix * viewMatrix * projectionMatrix;
}

void IShader::SetProjectionMatrix( const Matrix4& value )
{
	projectionMatrix = value;
	UpdateMVPMatrix();
}

void IShader::SetViewMatrix( const Matrix4& value )
{
	viewMatrix = value;
	UpdateMVPMatrix();
}

void IShader::SetModelMatrix( const Matrix4& value )
{
	modelMatrix = value;
	UpdateMVPMatrix();
}
