#include "Camera.h"
#include "Vector3.h"
#include "ShaderController.h"

using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Graphics;

Camera::Camera( GameObject* owner ) : IComponent( owner ), viewMatrix( Matrix4::Identity ) { }

void Camera::Update( void )
{
	const Vector3& position = owner->transform.Position();

	Vector3 up = owner->transform.RotationMatrix() * Vector3::Up;
	Vector3 lookAt = owner->transform.RotationMatrix() * Vector3::Forward;

	//up += owner->transform.Position();
	lookAt += position;

	Vector3 zAxis = ( lookAt - position ).Normalize();
	Vector3 xAxis = up.Cross( zAxis ).Normalize();
	Vector3 yAxis = zAxis.Cross( xAxis );

	// Set the computed values in the matrix
	viewMatrix.dataArray[ 0 ] = xAxis.x;
	viewMatrix.dataArray[ 1 ] = yAxis.x;
	viewMatrix.dataArray[ 2 ] = zAxis.x;
	viewMatrix.dataArray[ 3 ] = 0.0f;

	viewMatrix.dataArray[ 4 ] = xAxis.y;
	viewMatrix.dataArray[ 5 ] = yAxis.y;
	viewMatrix.dataArray[ 6 ] = zAxis.y;
	viewMatrix.dataArray[ 7 ] = 0.0f;

	viewMatrix.dataArray[ 8 ] = xAxis.z;
	viewMatrix.dataArray[ 9 ] = yAxis.z;
	viewMatrix.dataArray[ 10 ] = zAxis.z;
	viewMatrix.dataArray[ 11 ] = 0.0f;

	viewMatrix.dataArray[ 12 ] = -xAxis.Dot( position );
	viewMatrix.dataArray[ 13 ] = -yAxis.Dot( position );
	viewMatrix.dataArray[ 14 ] = -zAxis.Dot( position );
	viewMatrix.dataArray[ 15 ] = 1.0f;
}

void Camera::Draw( void )
{
	ISingleton<ShaderController>::Get().SetAllShadersUniform( "cameraMatrix", viewMatrix );
}

void Camera::Shutdown( void )
{

}