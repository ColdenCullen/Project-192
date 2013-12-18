#include "Camera.h"
#include "Vector3.h"
#include "ShaderController.h"

using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Graphics;

Camera::Camera( GameObject* owner ) : IComponent( owner ), viewMatrix( new Matrix4( Matrix4::Identity ) ) { }

void Camera::Update( void )
{
	const Vector3* position = owner->transform->Position();

	Vector3 up = *owner->transform->GetUp();
	//Vector3 up = Vector3::Up;
	Vector3 lookAt = *owner->transform->GetForward();
	//Vector3 lookAt = Vector3::Forward;

	// Don't do this
	//up += *owner->transform->Position();
	lookAt += *position;

	Vector3 zAxis = ( lookAt - *position ).Normalize();
	Vector3 xAxis = up.Cross( zAxis ).Normalize();
	Vector3 yAxis = zAxis.Cross( xAxis ).Normalize();

	//*
	// Set the computed values in the matrix
	viewMatrix->dataArray[ 0 ] = xAxis.x;
	viewMatrix->dataArray[ 1 ] = yAxis.x;
	viewMatrix->dataArray[ 2 ] = zAxis.x;
	viewMatrix->dataArray[ 3 ] = 0.0f;

	viewMatrix->dataArray[ 4 ] = xAxis.y;
	viewMatrix->dataArray[ 5 ] = yAxis.y;
	viewMatrix->dataArray[ 6 ] = zAxis.y;
	viewMatrix->dataArray[ 7 ] = 0.0f;

	viewMatrix->dataArray[ 8 ] = xAxis.z;
	viewMatrix->dataArray[ 9 ] = yAxis.z;
	viewMatrix->dataArray[ 10 ] = zAxis.z;
	viewMatrix->dataArray[ 11 ] = 0.0f;

	viewMatrix->dataArray[ 12 ] = -xAxis.Dot( *position );
	viewMatrix->dataArray[ 13 ] = -yAxis.Dot( *position );
	viewMatrix->dataArray[ 14 ] = -zAxis.Dot( *position );
	viewMatrix->dataArray[ 15 ] = 1.0f;
	//*/
	
	/*
	gFloat x = owner->transform->Position()->x;
	gFloat y = owner->transform->Position()->y;
	gFloat z = owner->transform->Position()->z;

	Matrix4 rotationMatrix = owner->transform->ToRotationMatrix( owner->transform->Rotation() );
	gFloat* rotMat = rotationMatrix.dataArray;

	// Set the computed values in the matrix
	viewMatrix->dataArray[ 0 ] = rotationMatrix.dataArray[0];
	viewMatrix->dataArray[ 1 ] = rotationMatrix.dataArray[1];
	viewMatrix->dataArray[ 2 ] = rotationMatrix.dataArray[2];
	viewMatrix->dataArray[ 3 ] = 0.0f;
	
	viewMatrix->dataArray[ 4 ] = rotationMatrix.dataArray[4];
	viewMatrix->dataArray[ 5 ] = rotationMatrix.dataArray[5];
	viewMatrix->dataArray[ 6 ] = rotationMatrix.dataArray[6];
	viewMatrix->dataArray[ 7 ] = 0.0f;
	
	viewMatrix->dataArray[ 8 ] = rotationMatrix.dataArray[8];
	viewMatrix->dataArray[ 9 ] = rotationMatrix.dataArray[9];
	viewMatrix->dataArray[ 10 ] = rotationMatrix.dataArray[10];
	viewMatrix->dataArray[ 11 ] = 0.0f;
	
	viewMatrix->dataArray[ 12 ] = -( rotMat[0] * x + rotMat[4] * y + rotMat[8] * z );
	viewMatrix->dataArray[ 13 ] = -( rotMat[1] * x + rotMat[5] * y + rotMat[9] * z );
	viewMatrix->dataArray[ 14 ] = ( rotMat[2] * x + rotMat[6] * y + rotMat[10] * z );
	viewMatrix->dataArray[ 15 ] = 1.0f;
	*/

	/*
	// Convert the camera position into a translation matrix.
	// Remember that to translate the camera, we actually translate the world in the opposite direction.
	Matrix4 translationMatrix(
		1.0f, 0.0f, 0.0f, -owner->transform->Position()->x,
		0.0f, 1.0f, 0.0f, -owner->transform->Position()->y,
		0.0f, 0.0f, 1.0f, -owner->transform->Position()->z,
		0.0f, 0.0f, 0.0f, 1.0f
		);

	// Convert the orientation quaternion into a rotation matrix.
	Matrix4 rotationMatrix = owner->transform->ToRotationMatrix( owner->transform->Rotation() );

	// Multiply the two matrices to get the camera view matrix.
	*viewMatrix = translationMatrix * rotationMatrix;
	*/
}

void Camera::Draw( void )
{
	//ShaderController::SetAllShadersUniform( "cameraMatrix", viewMatrix );
}

void Camera::Shutdown( void )
{

}

