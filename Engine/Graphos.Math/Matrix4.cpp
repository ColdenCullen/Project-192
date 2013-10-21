#include "Matrix4.h"
#include <math.h>

using namespace Graphos::Math;



const Matrix4 Matrix4::Identity = Matrix4(
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
);

Matrix4 Matrix4::operator*( const Matrix4& other ) const
{
	return Matrix4(
		( dataArray[ 0 ] * other.dataArray[ 0 ] ) + ( dataArray[ 1 ] * other.dataArray[ 4 ] ) + ( dataArray[ 2 ] * other.dataArray[ 8 ] ) + ( dataArray[ 3 ] * other.dataArray[ 12 ] ),
		( dataArray[ 0 ] * other.dataArray[ 1 ] ) + ( dataArray[ 1 ] * other.dataArray[ 5 ] ) + ( dataArray[ 2 ] * other.dataArray[ 9 ] ) + ( dataArray[ 3 ] * other.dataArray[ 13 ] ),
		( dataArray[ 0 ] * other.dataArray[ 2 ] ) + ( dataArray[ 1 ] * other.dataArray[ 6 ] ) + ( dataArray[ 2 ] * other.dataArray[ 10 ] ) + ( dataArray[ 3 ] * other.dataArray[ 14 ] ),
		( dataArray[ 0 ] * other.dataArray[ 3 ] ) + ( dataArray[ 1 ] * other.dataArray[ 7 ] ) + ( dataArray[ 2 ] * other.dataArray[ 11 ] ) + ( dataArray[ 3 ] * other.dataArray[ 15 ] ),

		( dataArray[ 4 ] * other.dataArray[ 0 ] ) + ( dataArray[ 5 ] * other.dataArray[ 4 ] ) + ( dataArray[ 6 ] * other.dataArray[ 8 ] ) + ( dataArray[ 7 ] * other.dataArray[ 12 ] ),
		( dataArray[ 4 ] * other.dataArray[ 1 ] ) + ( dataArray[ 5 ] * other.dataArray[ 5 ] ) + ( dataArray[ 6 ] * other.dataArray[ 9 ] ) + ( dataArray[ 7 ] * other.dataArray[ 13 ] ),
		( dataArray[ 4 ] * other.dataArray[ 2 ] ) + ( dataArray[ 5 ] * other.dataArray[ 6 ] ) + ( dataArray[ 6 ] * other.dataArray[ 10 ] ) + ( dataArray[ 7 ] * other.dataArray[ 14 ] ),
		( dataArray[ 4 ] * other.dataArray[ 3 ] ) + ( dataArray[ 5 ] * other.dataArray[ 7 ] ) + ( dataArray[ 6 ] * other.dataArray[ 11 ] ) + ( dataArray[ 7 ] * other.dataArray[ 15 ] ),

		( dataArray[ 8 ] * other.dataArray[ 0 ] ) + ( dataArray[ 9 ] * other.dataArray[ 4 ] ) + ( dataArray[ 10 ] * other.dataArray[ 8 ] ) + ( dataArray[ 11 ] * other.dataArray[ 12 ] ),
		( dataArray[ 8 ] * other.dataArray[ 1 ] ) + ( dataArray[ 9 ] * other.dataArray[ 5 ] ) + ( dataArray[ 10 ] * other.dataArray[ 9 ] ) + ( dataArray[ 11 ] * other.dataArray[ 13 ] ),
		( dataArray[ 8 ] * other.dataArray[ 2 ] ) + ( dataArray[ 9 ] * other.dataArray[ 6 ] ) + ( dataArray[ 10 ] * other.dataArray[ 10 ] ) + ( dataArray[ 11 ] * other.dataArray[ 14 ] ),
		( dataArray[ 8 ] * other.dataArray[ 3 ] ) + ( dataArray[ 9 ] * other.dataArray[ 7 ] ) + ( dataArray[ 10 ] * other.dataArray[ 11 ] ) + ( dataArray[ 11 ] * other.dataArray[ 15 ] ),

		( dataArray[ 12 ] * other.dataArray[ 0 ] ) + ( dataArray[ 13 ] * other.dataArray[ 4 ] ) + ( dataArray[ 14 ] * other.dataArray[ 8 ] ) + ( dataArray[ 15 ] * other.dataArray[ 12 ] ),
		( dataArray[ 12 ] * other.dataArray[ 1 ] ) + ( dataArray[ 13 ] * other.dataArray[ 5 ] ) + ( dataArray[ 14 ] * other.dataArray[ 9 ] ) + ( dataArray[ 15 ] * other.dataArray[ 13 ] ),
		( dataArray[ 12 ] * other.dataArray[ 2 ] ) + ( dataArray[ 13 ] * other.dataArray[ 6 ] ) + ( dataArray[ 14 ] * other.dataArray[ 10 ] ) + ( dataArray[ 15 ] * other.dataArray[ 14 ] ),
		( dataArray[ 12 ] * other.dataArray[ 3 ] ) + ( dataArray[ 13 ] * other.dataArray[ 7 ] ) + ( dataArray[ 14 ] * other.dataArray[ 11 ] ) + ( dataArray[ 15 ] * other.dataArray[ 15 ] )
	);
}

Matrix4 Matrix4::operator+( const Matrix4& other ) const
{
	Matrix4 toReturn;

	for( int ii = 0; ii < 16; ++ii )
		toReturn.dataArray[ ii ] = dataArray[ ii ] + other.dataArray[ ii ];

	return toReturn;
}

Matrix4& Matrix4::operator*=( const Matrix4& other )
{
	float result[ 16 ];

	// Perform multiply, store in result
	result[ 0 ] = ( dataArray[ 0 ] * other.dataArray[ 0 ] ) + ( dataArray[ 1 ] * other.dataArray[ 4 ] ) + ( dataArray[ 2 ] * other.dataArray[ 8 ] ) + ( dataArray[ 3 ] * other.dataArray[ 12 ] );
	result[ 1 ] = ( dataArray[ 0 ] * other.dataArray[ 1 ] ) + ( dataArray[ 1 ] * other.dataArray[ 5 ] ) + ( dataArray[ 2 ] * other.dataArray[ 9 ] ) + ( dataArray[ 3 ] * other.dataArray[ 13 ] );
	result[ 2 ] = ( dataArray[ 0 ] * other.dataArray[ 2 ] ) + ( dataArray[ 1 ] * other.dataArray[ 6 ] ) + ( dataArray[ 2 ] * other.dataArray[ 10 ] ) + ( dataArray[ 3 ] * other.dataArray[ 14 ] );
	result[ 3 ] = ( dataArray[ 0 ] * other.dataArray[ 3 ] ) + ( dataArray[ 1 ] * other.dataArray[ 7 ] ) + ( dataArray[ 2 ] * other.dataArray[ 11 ] ) + ( dataArray[ 3 ] * other.dataArray[ 15 ] );

	result[ 4 ] = ( dataArray[ 4 ] * other.dataArray[ 0 ] ) + ( dataArray[ 5 ] * other.dataArray[ 4 ] ) + ( dataArray[ 6 ] * other.dataArray[ 8 ] ) + ( dataArray[ 7 ] * other.dataArray[ 12 ] );
	result[ 5 ] = ( dataArray[ 4 ] * other.dataArray[ 1 ] ) + ( dataArray[ 5 ] * other.dataArray[ 5 ] ) + ( dataArray[ 6 ] * other.dataArray[ 9 ] ) + ( dataArray[ 7 ] * other.dataArray[ 13 ] );
	result[ 6 ] = ( dataArray[ 4 ] * other.dataArray[ 2 ] ) + ( dataArray[ 5 ] * other.dataArray[ 6 ] ) + ( dataArray[ 6 ] * other.dataArray[ 10 ] ) + ( dataArray[ 7 ] * other.dataArray[ 14 ] );
	result[ 7 ] = ( dataArray[ 4 ] * other.dataArray[ 3 ] ) + ( dataArray[ 5 ] * other.dataArray[ 7 ] ) + ( dataArray[ 6 ] * other.dataArray[ 11 ] ) + ( dataArray[ 7 ] * other.dataArray[ 15 ] );

	result[ 8 ] = ( dataArray[ 8 ] * other.dataArray[ 0 ] ) + ( dataArray[ 9 ] * other.dataArray[ 4 ] ) + ( dataArray[ 10 ] * other.dataArray[ 8 ] ) + ( dataArray[ 11 ] * other.dataArray[ 12 ] );
	result[ 9 ] = ( dataArray[ 8 ] * other.dataArray[ 1 ] ) + ( dataArray[ 9 ] * other.dataArray[ 5 ] ) + ( dataArray[ 10 ] * other.dataArray[ 9 ] ) + ( dataArray[ 11 ] * other.dataArray[ 13 ] );
	result[ 10 ] = ( dataArray[ 8 ] * other.dataArray[ 2 ] ) + ( dataArray[ 9 ] * other.dataArray[ 6 ] ) + ( dataArray[ 10 ] * other.dataArray[ 10 ] ) + ( dataArray[ 11 ] * other.dataArray[ 14 ] );
	result[ 11 ] = ( dataArray[ 8 ] * other.dataArray[ 3 ] ) + ( dataArray[ 9 ] * other.dataArray[ 7 ] ) + ( dataArray[ 10 ] * other.dataArray[ 11 ] ) + ( dataArray[ 11 ] * other.dataArray[ 15 ] );

	result[ 12 ] = ( dataArray[ 12 ] * other.dataArray[ 0 ] ) + ( dataArray[ 13 ] * other.dataArray[ 4 ] ) + ( dataArray[ 14 ] * other.dataArray[ 8 ] ) + ( dataArray[ 15 ] * other.dataArray[ 12 ] );
	result[ 13 ] = ( dataArray[ 12 ] * other.dataArray[ 1 ] ) + ( dataArray[ 13 ] * other.dataArray[ 5 ] ) + ( dataArray[ 14 ] * other.dataArray[ 9 ] ) + ( dataArray[ 15 ] * other.dataArray[ 13 ] );
	result[ 14 ] = ( dataArray[ 12 ] * other.dataArray[ 2 ] ) + ( dataArray[ 13 ] * other.dataArray[ 6 ] ) + ( dataArray[ 14 ] * other.dataArray[ 10 ] ) + ( dataArray[ 15 ] * other.dataArray[ 14 ] );
	result[ 15 ] = ( dataArray[ 12 ] * other.dataArray[ 3 ] ) + ( dataArray[ 13 ] * other.dataArray[ 7 ] ) + ( dataArray[ 14 ] * other.dataArray[ 11 ] ) + ( dataArray[ 15 ] * other.dataArray[ 15 ] );

	// Transfer results across
	for( int ii = 0; ii < 16; ++ii )
		dataArray[ ii ] = result[ ii ];

	return *this;
}

Matrix4& Matrix4::operator+=( const Matrix4& other )
{
	for( int ii = 0; ii < 16; ++ii )
		dataArray[ ii ] += other.dataArray[ ii ];

	return *this;
}

bool Matrix4::operator==( const Matrix4& other ) const
{
	for( int ii = 0; ii < 16; ++ii )
		if( dataArray[ ii ] != other.dataArray[ ii ] )
			return false;

	return true;
}

Matrix4 Matrix4::BuildPerspective( const float fov, const float screenAspect, const float near, const float depth )
{
	Matrix4 toReturn = Matrix4::Identity;

	toReturn.matrix[ 0 ][ 0 ] = 1.0f / ( screenAspect * tan( fov * 0.5f ) );
	toReturn.matrix[ 1 ][ 1 ] = 1.0f / tan( fov * 0.5f );
	toReturn.matrix[ 2 ][ 2 ] = depth / ( depth - near );
	toReturn.matrix[ 2 ][ 3 ] = 1.0f;
	toReturn.matrix[ 3 ][ 2 ] = ( -near * depth ) / ( depth - near );
	toReturn.matrix[ 3 ][ 3 ] = 0.0f;

	return toReturn;
}

Matrix4 Matrix4::BuildOrthogonal( const float width, const float height, const float near, const float far )
{
	Matrix4 toReturn = Matrix4::Identity;

	toReturn.matrix[ 0 ][ 0 ] = 2.0f / width;
	toReturn.matrix[ 1 ][ 1 ] = 2.0f / height;
	toReturn.matrix[ 2 ][ 2 ] = 1.0f / ( far - near );
	toReturn.matrix[ 3 ][ 2 ] = near / ( near - far );

	// Set to be 0,0 - width,height
	//toReturn.matrix[ 3 ][ 0 ] = -1.0f;
	//toReturn.matrix[ 3 ][ 1 ] = -1.0f;

	return toReturn;
}

Vector3 Matrix4::operator*( const Vector3& vec ) const
{
	return Vector3(
		matrix[ 0 ][ 0 ] * vec.x + matrix[ 1 ][ 0 ] * vec.y + matrix[ 2 ][ 0 ] * vec.z,
		matrix[ 0 ][ 1 ] * vec.x + matrix[ 1 ][ 1 ] * vec.y + matrix[ 2 ][ 1 ] * vec.z,
		matrix[ 0 ][ 2 ] * vec.x + matrix[ 1 ][ 2 ] * vec.y + matrix[ 2 ][ 2 ] * vec.z
	);
}

// I DON'T EVEN (borrowed from http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix)
Matrix4 Matrix4::Inverse( void ) const
{
	Matrix4 toReturn;
	float det;

	toReturn.dataArray[ 0 ] = dataArray[ 5 ]  * dataArray[ 10 ] * dataArray[ 15 ] - 
		dataArray[ 5 ]  * dataArray[ 11 ] * dataArray[ 14 ] - 
		dataArray[ 9 ]  * dataArray[ 6 ]  * dataArray[ 15 ] + 
		dataArray[ 9 ]  * dataArray[ 7 ]  * dataArray[ 14 ] +
		dataArray[ 13 ] * dataArray[ 6 ]  * dataArray[ 11 ] - 
		dataArray[ 13 ] * dataArray[ 7 ]  * dataArray[ 10 ];

	toReturn.dataArray[ 4 ] = -dataArray[ 4 ]  * dataArray[ 10 ] * dataArray[ 15 ] + 
		dataArray[ 4 ]  * dataArray[ 11 ] * dataArray[ 14 ] + 
		dataArray[ 8 ]  * dataArray[ 6 ]  * dataArray[ 15 ] - 
		dataArray[ 8 ]  * dataArray[ 7 ]  * dataArray[ 14 ] - 
		dataArray[ 12 ] * dataArray[ 6 ]  * dataArray[ 11 ] + 
		dataArray[ 12 ] * dataArray[ 7 ]  * dataArray[ 10 ];

	toReturn.dataArray[ 8 ] = dataArray[ 4 ]  * dataArray[ 9 ] * dataArray[ 15 ] - 
		dataArray[ 4 ]  * dataArray[ 11 ] * dataArray[ 13 ] - 
		dataArray[ 8 ]  * dataArray[ 5 ]  * dataArray[ 15 ] + 
		dataArray[ 8 ]  * dataArray[ 7 ]  * dataArray[ 13 ] + 
		dataArray[ 12 ] * dataArray[ 5 ]  * dataArray[ 11 ] - 
		dataArray[ 12 ] * dataArray[ 7 ]  * dataArray[ 9 ];

	toReturn.dataArray[ 12 ] = -dataArray[ 4 ]  * dataArray[ 9 ] * dataArray[ 14 ] + 
		dataArray[ 4 ]  * dataArray[ 10 ] * dataArray[ 13 ] +
		dataArray[ 8 ]  * dataArray[ 5 ]  * dataArray[ 14 ] - 
		dataArray[ 8 ]  * dataArray[ 6 ]  * dataArray[ 13 ] - 
		dataArray[ 12 ] * dataArray[ 5 ]  * dataArray[ 10 ] + 
		dataArray[ 12 ] * dataArray[ 6 ]  * dataArray[ 9 ];

	toReturn.dataArray[ 1 ] = -dataArray[ 1 ]  * dataArray[ 10 ] * dataArray[ 15 ] + 
		dataArray[ 1 ]  * dataArray[ 11 ] * dataArray[ 14 ] + 
		dataArray[ 9 ]  * dataArray[ 2 ]  * dataArray[ 15 ] - 
		dataArray[ 9 ]  * dataArray[ 3 ]  * dataArray[ 14 ] - 
		dataArray[ 13 ] * dataArray[ 2 ]  * dataArray[ 11 ] + 
		dataArray[ 13 ] * dataArray[ 3 ]  * dataArray[ 10 ];

	toReturn.dataArray[ 5 ] = dataArray[ 0 ]  * dataArray[ 10 ] * dataArray[ 15 ] - 
		dataArray[ 0 ]  * dataArray[ 11 ] * dataArray[ 14 ] - 
		dataArray[ 8 ]  * dataArray[ 2 ]  * dataArray[ 15 ] + 
		dataArray[ 8 ]  * dataArray[ 3 ]  * dataArray[ 14 ] + 
		dataArray[ 12 ] * dataArray[ 2 ]  * dataArray[ 11 ] - 
		dataArray[ 12 ] * dataArray[ 3 ]  * dataArray[ 10 ];

	toReturn.dataArray[ 9 ] = -dataArray[ 0 ]  * dataArray[ 9 ] * dataArray[ 15 ] + 
		dataArray[ 0 ]  * dataArray[ 11 ] * dataArray[ 13 ] + 
		dataArray[ 8 ]  * dataArray[ 1 ]  * dataArray[ 15 ] - 
		dataArray[ 8 ]  * dataArray[ 3 ]  * dataArray[ 13 ] - 
		dataArray[ 12 ] * dataArray[ 1 ]  * dataArray[ 11 ] + 
		dataArray[ 12 ] * dataArray[ 3 ]  * dataArray[ 9 ];

	toReturn.dataArray[ 13 ] = dataArray[ 0 ]  * dataArray[ 9 ] * dataArray[ 14 ] - 
		dataArray[ 0 ]  * dataArray[ 10 ] * dataArray[ 13 ] - 
		dataArray[ 8 ]  * dataArray[ 1 ]  * dataArray[ 14 ] + 
		dataArray[ 8 ]  * dataArray[ 2 ]  * dataArray[ 13 ] + 
		dataArray[ 12 ] * dataArray[ 1 ]  * dataArray[ 10 ] - 
		dataArray[ 12 ] * dataArray[ 2 ]  * dataArray[ 9 ];

	toReturn.dataArray[ 2 ] = dataArray[ 1 ]  * dataArray[ 6 ] * dataArray[ 15 ] - 
		dataArray[ 1 ]  * dataArray[ 7 ] * dataArray[ 14 ] - 
		dataArray[ 5 ]  * dataArray[ 2 ] * dataArray[ 15 ] + 
		dataArray[ 5 ]  * dataArray[ 3 ] * dataArray[ 14 ] + 
		dataArray[ 13 ] * dataArray[ 2 ] * dataArray[ 7 ] - 
		dataArray[ 13 ] * dataArray[ 3 ] * dataArray[ 6 ];

	toReturn.dataArray[ 6 ] = -dataArray[ 0]  * dataArray[ 6 ] * dataArray[ 15 ] + 
		dataArray[ 0 ]  * dataArray[ 7 ] * dataArray[ 14 ] + 
		dataArray[ 4 ]  * dataArray[ 2 ] * dataArray[ 15 ] - 
		dataArray[ 4 ]  * dataArray[ 3 ] * dataArray[ 14 ] - 
		dataArray[ 12 ] * dataArray[ 2 ] * dataArray[ 7 ] + 
		dataArray[ 12 ] * dataArray[ 3 ] * dataArray[ 6 ];

	toReturn.dataArray[ 10 ] = dataArray[ 0 ]  * dataArray[ 5 ] * dataArray[ 15 ] - 
		dataArray[ 0 ]  * dataArray[ 7 ] * dataArray[ 13 ] - 
		dataArray[ 4 ]  * dataArray[ 1 ] * dataArray[ 15 ] + 
		dataArray[ 4 ]  * dataArray[ 3 ] * dataArray[ 13 ] + 
		dataArray[ 12 ] * dataArray[ 1 ] * dataArray[ 7 ] - 
		dataArray[ 12 ] * dataArray[ 3 ] * dataArray[ 5 ];

	toReturn.dataArray[ 14 ] = -dataArray[ 0 ]  * dataArray[ 5 ] * dataArray[ 14 ] + 
		dataArray[ 0 ]  * dataArray[ 6 ] * dataArray[ 13 ] + 
		dataArray[ 4 ]  * dataArray[ 1 ] * dataArray[ 14 ] - 
		dataArray[ 4 ]  * dataArray[ 2 ] * dataArray[ 13 ] - 
		dataArray[ 12 ] * dataArray[ 1 ] * dataArray[ 6 ] + 
		dataArray[ 12 ] * dataArray[ 2 ] * dataArray[ 5 ];

	toReturn.dataArray[ 3 ] = -dataArray[ 1 ] * dataArray[ 6 ] * dataArray[ 11 ] + 
		dataArray[ 1 ] * dataArray[ 7 ] * dataArray[ 10 ] + 
		dataArray[ 5 ] * dataArray[ 2 ] * dataArray[ 11 ] - 
		dataArray[ 5 ] * dataArray[ 3 ] * dataArray[ 10 ] - 
		dataArray[ 9 ] * dataArray[ 2 ] * dataArray[ 7 ] + 
		dataArray[ 9 ] * dataArray[ 3 ] * dataArray[ 6 ];

	toReturn.dataArray[ 7 ] = dataArray[ 0 ] * dataArray[ 6 ] * dataArray[ 11 ] - 
		dataArray[ 0 ] * dataArray[ 7 ] * dataArray[ 10 ] - 
		dataArray[ 4 ] * dataArray[ 2 ] * dataArray[ 11 ] + 
		dataArray[ 4 ] * dataArray[ 3 ] * dataArray[ 10 ] + 
		dataArray[ 8 ] * dataArray[ 2 ] * dataArray[ 7 ] - 
		dataArray[ 8 ] * dataArray[ 3 ] * dataArray[ 6 ];

	toReturn.dataArray[ 11 ] = -dataArray[ 0 ] * dataArray[ 5 ] * dataArray[ 11 ] + 
		dataArray[ 0 ] * dataArray[ 7 ] * dataArray[ 9 ] + 
		dataArray[ 4 ] * dataArray[ 1 ] * dataArray[ 11 ] - 
		dataArray[ 4 ] * dataArray[ 3 ] * dataArray[ 9 ] - 
		dataArray[ 8 ] * dataArray[ 1 ] * dataArray[ 7 ] + 
		dataArray[ 8 ] * dataArray[ 3 ] * dataArray[ 5 ];

	toReturn.dataArray[ 15 ] = dataArray[ 0 ] * dataArray[ 5 ] * dataArray[ 10 ] - 
		dataArray[ 0 ] * dataArray[ 6 ] * dataArray[ 9 ] - 
		dataArray[ 4 ] * dataArray[ 1 ] * dataArray[ 10 ] + 
		dataArray[ 4 ] * dataArray[ 2 ] * dataArray[ 9 ] + 
		dataArray[ 8 ] * dataArray[ 1 ] * dataArray[ 6 ] - 
		dataArray[ 8 ] * dataArray[ 2 ] * dataArray[ 5 ];

	det = 1.0f / (
		dataArray[ 0 ] * toReturn.dataArray[ 0 ] +
		dataArray[ 1 ] * toReturn.dataArray[ 4 ] +
		dataArray[ 2 ] * toReturn.dataArray[ 8 ] +
		dataArray[ 3 ] * toReturn.dataArray[ 12 ]
	);

	for( int ii = 0; ii < 16; ++ii )
		toReturn.dataArray[ ii ] *= det;

	return toReturn;
}