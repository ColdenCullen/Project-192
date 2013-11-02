#include "IShader.h"

using namespace std;
using namespace v8;
using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Graphics;


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
