#include "IShader.h"

using namespace std;
using namespace v8;
using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Graphics;


void IShader::UpdateMVPMatrix( void )
{
	delete modelViewProjection;
	modelViewProjection = new Matrix4( *modelMatrix * *viewMatrix * *projectionMatrix );
}

void IShader::SetProjectionMatrix( const Matrix4& value )
{
	*projectionMatrix = value;
	UpdateMVPMatrix();
}

void IShader::SetViewMatrix( const Matrix4& value )
{
	*viewMatrix = value;
	UpdateMVPMatrix();
}

void IShader::SetModelMatrix( const Matrix4& value )
{
	*modelMatrix = value;
	UpdateMVPMatrix();
}

void IShader::Shutdown( void )
{
	delete_s( modelMatrix );
	delete_s( viewMatrix );
	delete_s( projectionMatrix );
	delete_s( modelViewProjection );
}
void IShader::SetUniformMatrix( std::string name, const Matrix4& matrix ) const
{
	throw exception( "Not implemented!" );
}

void IShader::SetUniformArray( std::string name, const int* value, const int size ) const
{
	throw exception( "Not implemented!" );
}

void IShader::SetUniformArray( std::string name, const float* value, const int size ) const
{
	throw exception( "Not implemented!" );
}

void IShader::SetUniform( std::string name, const int value ) const
{
	throw exception( "Not implemented!" );
}

void IShader::SetUniform( std::string name, const float value ) const
{
	throw exception( "Not implemented!" );
}

void IShader::RegisterConstBuffer( std::string name, ConstBuffer* buf )
{
	throw exception( "Not implemented!" );
}

void IShader::BindTexture( Texture& text ) const
{
	throw exception( "Not implemented!" );
}

void IShader::Draw( Mesh& mesh ) const
{
	throw exception( "Not implemented!" );
}

IShader::IShader( void ) : modelMatrix( new Matrix4 ), viewMatrix( new Matrix4 ),
	projectionMatrix( new Matrix4 ), modelViewProjection( new Matrix4 )
{

}
