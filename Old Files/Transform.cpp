#include "Transform.h"

using namespace Graphos::Math;

Transform::Transform( void ) : parent( nullptr ), matrix( Matrix::Identity ), scale( Vector3( 1.0f, 1.0f, 1.0f ) ) { }

void Transform::Rotate( Quaternion rotation )
{
	Rotate( rotation.x, rotation.y, rotation.z, rotation.w );

	//matrix *= rotation.ToRotationMatrix();
}

void Transform::Rotate( const float x, const float y, const float z, const float angle )
{
	Vector3 oldCoord = position;

	Translate( -oldCoord );

	//TODO: Make better
	if( z != 0.0f ) matrix *= RotateZ( z * M_PI / 180 );
	if( x != 0.0f ) matrix *= RotateX( x * M_PI / 180 );
	if( y != 0.0f ) matrix *= RotateY( y * M_PI / 180 );

	rotation.x += x;
	rotation.y += y;
	rotation.z += z;

	Translate( oldCoord );
}

void Transform::Rotate( const float x, const float y, const float z )
{
	Vector3 oldCoord = position;

	Translate( -oldCoord );

	if( z != 0.0f ) matrix *= RotateZ( z * M_PI / 180 );
	if( x != 0.0f ) matrix *= RotateX( x * M_PI / 180 );
	if( y != 0.0f ) matrix *= RotateY( y * M_PI / 180 );
	
	rotation.x += x;
	rotation.y += y;
	rotation.z += z;

	Translate( oldCoord );
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

	position.x += x;
	position.y += y;
	position.z += z;
}

void Transform::Translate( const Vector3& displacement )
{
	Translate( displacement.x, displacement.y, displacement.z );
}

void Transform::Scale( const float x, const float y, const float z )
{
	Matrix scaleMatrix = Matrix::Identity;

	scaleMatrix.matrix[ 0 ][ 0 ] = x;
	scaleMatrix.matrix[ 1 ][ 1 ] = y;
	scaleMatrix.matrix[ 2 ][ 2 ] = z;

	matrix *= scaleMatrix;

	scale.x *= x;
	scale.y *= y;
	scale.z *= z;
}

void Transform::Scale( const Vector3& scale )
{
	Scale( scale.x, scale.y, scale.z );
}

Matrix Transform::RotateX( const float angle ) const
{
	Matrix newTrans = Matrix::Identity;

	newTrans.matrix[ 1 ][ 1 ] = cos( angle );
	newTrans.matrix[ 1 ][ 2 ] = -sin( angle );
	newTrans.matrix[ 2 ][ 1 ] = sin( angle );
	newTrans.matrix[ 2 ][ 2 ] = cos( angle );

	return newTrans;
}

Matrix Transform::RotateY( const float angle ) const
{
	Matrix newTrans = Matrix::Identity;

	newTrans.matrix[ 0 ][ 0 ] = cos( angle );
	newTrans.matrix[ 0 ][ 2 ] = -sin( angle );
	newTrans.matrix[ 2 ][ 0 ] = sin( angle );
	newTrans.matrix[ 2 ][ 2 ] = cos( angle );

	return newTrans;
}

Matrix Transform::RotateZ( const float angle ) const
{
	Matrix newTrans = Matrix::Identity;

	newTrans.matrix[ 0 ][ 0 ] = cos( angle );
	newTrans.matrix[ 0 ][ 1 ] = -sin( angle );
	newTrans.matrix[ 1 ][ 0 ] = sin( angle );
	newTrans.matrix[ 1 ][ 1 ] = cos( angle );

	return newTrans;
}

const Matrix Transform::WorldMatrix() const
{
	if( parent != nullptr ) return parent->WorldMatrix() * matrix;
	else					return matrix;
}

const Matrix Transform::RotationMatrix( void ) const
{
	Matrix x = RotateZ( rotation.z ) * RotateX( rotation.x ) * RotateY( rotation.y );
	return RotateZ( rotation.z ) * RotateX( rotation.x ) * RotateY( rotation.y );
}