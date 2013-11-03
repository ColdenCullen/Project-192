#include "Transform.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace Graphos::Math;

Transform::Transform( void ) :
	parent( nullptr ), matrix( Matrix4::Identity ), 
	position( new Vector3( 0.0f, 0.0f, 0.0f ) ), rotation( new Vector3( 0.0f, 0.0f, 0.0f ) ), scale( new Vector3( 1.0f, 1.0f, 1.0f ) ),
	right( new Vector3( Vector3::Right ) ), up( new Vector3( Vector3::Up ) ), forward( new Vector3( Vector3::Forward ) ) { }

Transform::~Transform( void )
{
	delete_s( position );
	delete_s( rotation );
	delete_s( scale );
	delete_s( right );
	delete_s( up );
	delete_s( forward );
}

void Transform::Rotate( const Quaternion& rotation )
{
	Rotate( rotation.x, rotation.y, rotation.z, rotation.w );

	// For future reference
	//this->rotation *= rotation;
	//matrix *= rotation.ToRotationMatrix();
}

void Transform::Rotate( const float x, const float y, const float z, const float w )
{
	// For future reference
	//Rotate( Quaternion( x, y, z, angle ) );

	Vector3 oldCoord = *position;

	Translate( -oldCoord );

	//TODO: Make better
	if( z != 0.0f ) matrix *= RotateZ( z );
	if( x != 0.0f ) matrix *= RotateX( x );
	if( y != 0.0f ) matrix *= RotateY( y );

	rotation->x += x;
	rotation->y += y;
	rotation->z += z;

	Translate( oldCoord );

	UpdateLocalVectors();
}

void Transform::Rotate( const float x, const float y, const float z )
{
	Vector3 oldCoord = *position;

	Translate( -oldCoord );

	if( z != 0.0f ) matrix *= RotateZ( z * M_PI / 180 );
	if( x != 0.0f ) matrix *= RotateX( x * M_PI / 180 );
	if( y != 0.0f ) matrix *= RotateY( y * M_PI / 180 );
	
	rotation->x += x;
	rotation->y += y;
	rotation->z += z;

	Translate( oldCoord );

	UpdateLocalVectors();
}

void Transform::Rotate( const Vector3& eulerAngles )
{
	Rotate( eulerAngles.x, eulerAngles.y, eulerAngles.z );
}

void Transform::Translate( const float x, const float y, const float z )
{
	matrix.matrix[ 3 ][ 0 ] += x;
	matrix.matrix[ 3 ][ 1 ] += y;
	matrix.matrix[ 3 ][ 2 ] += z;

	position->x += x;
	position->y += y;
	position->z += z;
}

void Transform::Translate( const Vector3& displacement )
{
	Translate( displacement.x, displacement.y, displacement.z );
}

void Graphos::Math::Transform::TranslateTo( const float x, const float y, const float z )
{
	matrix.matrix[ 3 ][ 0 ] = x;
	matrix.matrix[ 3 ][ 1 ] = y;
	matrix.matrix[ 3 ][ 2 ] = z;

	position->x = x;
	position->y = y;
	position->z = z;
}

void Graphos::Math::Transform::TranslateTo( const Vector3& newLocation )
{
	TranslateTo( newLocation.x, newLocation.y, newLocation.z );
}

void Transform::Scale( const float x, const float y, const float z )
{
	Matrix4 scaleMatrix = Matrix4::Identity;

	scaleMatrix.matrix[ 0 ][ 0 ] = x;
	scaleMatrix.matrix[ 1 ][ 1 ] = y;
	scaleMatrix.matrix[ 2 ][ 2 ] = z;

	matrix *= scaleMatrix;

	scale->x *= x;
	scale->y *= y;
	scale->z *= z;
}

void Transform::Scale( const Vector3& scale )
{
	Scale( scale.x, scale.y, scale.z );
}

Matrix4 Transform::RotateX( const float angle ) const
{
	Matrix4 newTrans = Matrix4::Identity;

	newTrans.matrix[ 1 ][ 1 ] = cos( angle );
	newTrans.matrix[ 1 ][ 2 ] = -sin( angle );
	newTrans.matrix[ 2 ][ 1 ] = sin( angle );
	newTrans.matrix[ 2 ][ 2 ] = cos( angle );

	return newTrans;
}

Matrix4 Transform::RotateY( const float angle ) const
{
	Matrix4 newTrans = Matrix4::Identity;

	newTrans.matrix[ 0 ][ 0 ] = cos( angle );
	newTrans.matrix[ 0 ][ 2 ] = -sin( angle );
	newTrans.matrix[ 2 ][ 0 ] = sin( angle );
	newTrans.matrix[ 2 ][ 2 ] = cos( angle );

	return newTrans;
}

Matrix4 Transform::RotateZ( const float angle ) const
{
	Matrix4 newTrans = Matrix4::Identity;

	newTrans.matrix[ 0 ][ 0 ] = cos( angle );
	newTrans.matrix[ 0 ][ 1 ] = -sin( angle );
	newTrans.matrix[ 1 ][ 0 ] = sin( angle );
	newTrans.matrix[ 1 ][ 1 ] = cos( angle );

	return newTrans;
}

Matrix4& Transform::WorldMatrix()
{
	if( parent != nullptr ) return parent->WorldMatrix() * matrix;
	else					return matrix;
}

const Matrix4 Transform::RotationMatrix( void ) const
{
	Matrix4 x = RotateZ( rotation->z ) * RotateX( rotation->x ) * RotateY( rotation->y );
	return RotateZ( rotation->z ) * RotateX( rotation->x ) * RotateY( rotation->y );
}

void Transform::UpdateLocalVectors( void )
{
	*right = RotationMatrix() * *right;
	*up = RotationMatrix() * *up;
	*forward = RotationMatrix() * *forward;
}


