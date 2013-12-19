#include "Transform.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace Graphos::Math;

Transform::Transform( void ) :
	parent( nullptr ), matrix( Matrix4::Identity ), 
	position( new Vector3( 0.0f, 0.0f, 0.0f ) ), rotation( new btQuaternion( 0.0f, 0.0f, 0.0f ) ), scale( new Vector3( 1.0f, 1.0f, 1.0f ) ),
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

// Convert to multiply-able rotation matrix
// DONE
Matrix4 Transform::ToRotationMatrix( const btQuaternion * quat ) const
{
	gFloat x = quat->x();
	gFloat y = quat->y();
	gFloat z = quat->z();
	gFloat w = quat->w();

	return Matrix4(
		(pow(w,2)+pow(x,2)-pow(y,2)-pow(z,2)), (2.0f*x*y-2.0f*w*z), (2.0f*x*z+2.0f*w*y), 0.0f,
		(2.0f*x*y+2.0f*w*z), (pow(w,2)-pow(x,2)+pow(y,2)-pow(z,2)), (2.0f*y*z-2.0f*w*x), 0.0f,
		(2.0f*x*z-2.0f*w*y), (2.0f*y*z+2.0f*w*x), (pow(w,2)-pow(x,2)-pow(y,2)+pow(z,2)), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

void Transform::Rotate( const btQuaternion& rotation, bool global )
{
	Vector3 oldCoord = *position;
	Translate( -oldCoord );

	if( global )
	{
		*this->rotation = (*this->rotation) * rotation;
		matrix = matrix * ToRotationMatrix( &rotation );
	}
	else
	{
		*this->rotation = rotation * (*this->rotation);
		matrix = ToRotationMatrix( &rotation ) * matrix;
	}

	Translate( oldCoord );

	UpdateLocalVectors();
}

void Transform::Rotate( const gFloat x, const gFloat y, const gFloat z, const gFloat w, bool global )
{
	Rotate( btQuaternion( btVector3( x, y, z ), w * M_PI / 180 ), global );
}

void Transform::Rotate( const gFloat x, const gFloat y, const gFloat z )
{
	btQuaternion newQuat;
	newQuat.setEuler( x, y, z );
	//newQuat.inverse();

	Rotate( newQuat, false );

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

void Graphos::Math::Transform::RotateTo( const btQuaternion& rotation )
{	
	// Save old data
	Vector3 oldScale = *scale;
	Vector3 oldPosition = *position;

	// Reset matrix
	matrix = Matrix4::Identity;

	// Translate
	TranslateTo( *position );

	// Revert scale to unit and then scale
	scale = new Vector3( 1.0f, 1.0f, 1.0f );
	Scale( oldScale );

	// Rotate
	*this->rotation = rotation;
	matrix *= ToRotationMatrix( &rotation ).Inverse();

}

void Transform::Scale( const gFloat x, const gFloat y, const gFloat z )
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

Matrix4& Transform::WorldMatrix()
{
	if( parent != nullptr ) return parent->WorldMatrix() * matrix;
	else					return matrix;
}

const Matrix4 Transform::RotationMatrix( void ) const
{
	return ToRotationMatrix( rotation );
}

// Changes up, forward and right vectors
void Transform::UpdateLocalVectors( void )
{
	gFloat qx = rotation->x();
	gFloat qy = rotation->y();
	gFloat qz = rotation->z();
	gFloat qw = rotation->w();

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


