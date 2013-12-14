#include "Transform.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace Graphos::Math;

Transform::Transform( void ) :
	parent( nullptr ), matrix( Matrix4::Identity ), 
	position( new Vector3( 0.0f, 0.0f, 0.0f ) ), rotation( new Quaternion( Vector3(), 1.0f ) ), scale( new Vector3( 1.0f, 1.0f, 1.0f ) ),
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
	Vector3 oldCoord = *position;
	Translate( -oldCoord );

	*this->rotation *= rotation;
	matrix *= rotation.ToRotationMatrix();

	Translate( oldCoord );

	UpdateLocalVectors();
}

void Transform::Rotate( const gFloat x, const gFloat y, const gFloat z, const gFloat w )
{
	Rotate( Quaternion( x, y, z, w * M_PI / 180 ) );
}

void Transform::Rotate( const gFloat x, const gFloat y, const gFloat z )
{
	if( z != 0.0f ) Roll( z * M_PI / 180 );
	if( x != 0.0f ) Pitch( x * M_PI / 180 );
	if( y != 0.0f ) Yaw( y * M_PI / 180 );
}

void Transform::Rotate( const Vector3& eulerAngles )
{
	Rotate( eulerAngles.x, eulerAngles.y, eulerAngles.z );
}

void Transform::Translate( const gFloat x, const gFloat y, const gFloat z )
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

void Graphos::Math::Transform::TranslateTo( const gFloat x, const gFloat y, const gFloat z )
{
	matrix.matrix[ 3 ][ 0 ] = position->x = x;
	matrix.matrix[ 3 ][ 1 ] = position->y = y;
	matrix.matrix[ 3 ][ 2 ] = position->z = z;
}

void Graphos::Math::Transform::TranslateTo( const Vector3& newLocation )
{
	TranslateTo( newLocation.x, newLocation.y, newLocation.z );
}

void Transform::Scale( const gFloat x, const gFloat y, const gFloat z )
{
	Matrix4 scaleMatrix = Matrix4::Identity;

	matrix.matrix[ 0 ][ 0 ] *= x;
	matrix.matrix[ 1 ][ 1 ] *= y;
	matrix.matrix[ 2 ][ 2 ] *= z;

	scale->x *= x;
	scale->y *= y;
	scale->z *= z;
}

void Transform::Scale( const Vector3& scale )
{
	Scale( scale.x, scale.y, scale.z );
}

void Transform::Pitch( const gFloat angle )
{
	Vector3 oldCoord = *position;
	Translate( -oldCoord );

	Matrix4 newTrans = Matrix4::Identity;

	newTrans.matrix[ 1 ][ 1 ] = cos( angle );
	newTrans.matrix[ 1 ][ 2 ] = -sin( angle );
	newTrans.matrix[ 2 ][ 1 ] = sin( angle );
	newTrans.matrix[ 2 ][ 2 ] = cos( angle );

	matrix *= newTrans;
	*rotation *= Quaternion( Vector3::Right, angle );

	Translate( oldCoord );

	UpdateLocalVectors();
}

void Transform::Yaw( const gFloat angle )
{
	Vector3 oldCoord = *position;
	Translate( -oldCoord );
	
	Matrix4 newTrans = Matrix4::Identity;

	newTrans.matrix[ 0 ][ 0 ] = cos( angle );
	newTrans.matrix[ 0 ][ 2 ] = sin( angle );
	newTrans.matrix[ 2 ][ 0 ] = -sin( angle );
	newTrans.matrix[ 2 ][ 2 ] = cos( angle );

	matrix *= newTrans;
	*rotation *= Quaternion( Vector3::Up, angle );

	Translate( oldCoord );

	UpdateLocalVectors();
}

void Transform::Roll( const gFloat angle )
{
	Vector3 oldCoord = *position;
	Translate( -oldCoord );

	Matrix4 newTrans = Matrix4::Identity;

	newTrans.matrix[ 0 ][ 0 ] = cos( angle );
	newTrans.matrix[ 0 ][ 1 ] = -sin( angle );
	newTrans.matrix[ 1 ][ 0 ] = sin( angle );
	newTrans.matrix[ 1 ][ 1 ] = cos( angle );

	matrix *= newTrans;
	*rotation *= Quaternion( Vector3::Forward, angle );

	Translate( oldCoord );

	UpdateLocalVectors();
}

Matrix4& Transform::WorldMatrix()
{
	if( parent != nullptr ) return parent->WorldMatrix() * matrix;
	else					return matrix;
}

const Matrix4 Transform::RotationMatrix( void ) const
{
	return rotation->ToRotationMatrix();
}

void Transform::UpdateLocalVectors( void )
{
	float qx = rotation->x;
	float qy = rotation->y;
	float qz = rotation->z;
	float qw = rotation->w;

	// Derive the local axis vectors from the orientation quaternion.
	*right = Vector3(
		1.0f - 2.0f * (qy * qy + qz * qz),
		2.0f * (qx * qy - qw * qz),
		2.0f * (qx * qz + qw * qy) );

	*up = Vector3(
		2.0f * (qx * qy + qw * qz),
		1.0f - 2.0f * (qx * qx + qz * qz),
		2.0f * (qy * qz - qw * qx) );

	*forward = Vector3(
		2.0f * (qx * qz - qw * qy),
		2.0f * (qy * qz + qw * qx),
		1.0f - 2.0f * (qx * qx + qy * qy) );
}
