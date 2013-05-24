#include "Matrix.h"
#include <math.h>

using namespace Graphos::Math;

const Matrix Matrix::Identity = Matrix(
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
);

Matrix Matrix::operator*( const Matrix& other ) const
{
	return Matrix(
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

Matrix Matrix::operator+( const Matrix& other ) const
{
	Matrix toReturn;

	for( int ii = 0; ii < 16; ++ii )
		toReturn.dataArray[ ii ] = dataArray[ ii ] + other.dataArray[ ii ];

	return toReturn;
}

void Matrix::operator*=( const Matrix& other )
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
}

void Matrix::operator+=( const Matrix& other )
{
	for( int ii = 0; ii < 16; ++ii )
		dataArray[ ii ] += other.dataArray[ ii ];
}

bool Matrix::operator==( const Matrix& other ) const
{
	for( int ii = 0; ii < 16; ++ii )
		if( dataArray[ ii ] != other.dataArray[ ii ] )
			return false;

	return true;
}

Matrix Matrix::BuildPerspective( const float fov, const float screenAspect, const float near, const float depth )
{
	Matrix toReturn = Matrix::Identity;

	toReturn.matrix[ 0 ][ 0 ] = 1.0f / ( screenAspect * tan( fov * 0.5f ) );
	toReturn.matrix[ 1 ][ 1 ] = 1.0f / tan( fov * 0.5f );
	toReturn.matrix[ 2 ][ 2 ] = depth / ( depth - near );
	toReturn.matrix[ 2 ][ 3 ] = 1.0f;
	toReturn.matrix[ 3 ][ 2 ] = ( -near * depth ) / ( depth - near );
	toReturn.matrix[ 3 ][ 3 ] = 0.0f;

	return toReturn;
}

Matrix Matrix::BuildOrthogonal( const float width, const float height, const float near, const float far )
{
	Matrix toReturn = Matrix::Identity;

	toReturn.matrix[ 0 ][ 0 ] = 2.0f / width;
	toReturn.matrix[ 1 ][ 1 ] = 2.0f / height;
	toReturn.matrix[ 2 ][ 2 ] = 1.0f / ( far - near );
	toReturn.matrix[ 3 ][ 2 ] = near / ( near - far );

	// Set to be 0,0 - width,height
	//toReturn.matrix[ 3 ][ 0 ] = -1.0f;
	//toReturn.matrix[ 3 ][ 1 ] = -1.0f;

	return toReturn;
}

Vector3 Matrix::operator*( const Vector3& vec ) const
{
	return Vector3(
		matrix[ 0 ][ 0 ] * vec.x + matrix[ 1 ][ 0 ] * vec.y + matrix[ 2 ][ 0 ] * vec.z,
		matrix[ 0 ][ 1 ] * vec.x + matrix[ 1 ][ 1 ] * vec.y + matrix[ 2 ][ 1 ] * vec.z,
		matrix[ 0 ][ 2 ] * vec.x + matrix[ 1 ][ 2 ] * vec.y + matrix[ 2 ][ 2 ] * vec.z
	);
}

// GAH (borrowed from http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix)
Matrix Matrix::Inverse( void ) const
{
	Matrix toReturn;
	float inv[16];
	float det;

	inv[ 0 ] = dataArray[ 5 ]  * dataArray[ 10 ] * dataArray[ 15 ] - 
		dataArray[ 5 ]  * dataArray[ 11 ] * dataArray[ 14 ] - 
		dataArray[ 9 ]  * dataArray[ 6 ]  * dataArray[ 15 ] + 
		dataArray[ 9 ]  * dataArray[ 7 ]  * dataArray[ 14 ] +
		dataArray[ 13 ] * dataArray[ 6 ]  * dataArray[ 11 ] - 
		dataArray[ 13 ] * dataArray[ 7 ]  * dataArray[ 10 ];

	inv[ 4 ] = -dataArray[ 4 ]  * dataArray[ 10 ] * dataArray[ 15 ] + 
		dataArray[ 4 ]  * dataArray[ 11 ] * dataArray[ 14 ] + 
		dataArray[ 8 ]  * dataArray[ 6 ]  * dataArray[ 15 ] - 
		dataArray[ 8 ]  * dataArray[ 7 ]  * dataArray[ 14 ] - 
		dataArray[ 12 ] * dataArray[ 6 ]  * dataArray[ 11 ] + 
		dataArray[ 12 ] * dataArray[ 7 ]  * dataArray[ 10 ];

	inv[ 8 ] = dataArray[ 4 ]  * dataArray[ 9 ] * dataArray[ 15 ] - 
		dataArray[ 4 ]  * dataArray[ 11 ] * dataArray[ 13 ] - 
		dataArray[ 8 ]  * dataArray[ 5 ]  * dataArray[ 15 ] + 
		dataArray[ 8 ]  * dataArray[ 7 ]  * dataArray[ 13 ] + 
		dataArray[ 12 ] * dataArray[ 5 ]  * dataArray[ 11 ] - 
		dataArray[ 12 ] * dataArray[ 7 ]  * dataArray[ 9 ];

	inv[ 12 ] = -dataArray[ 4 ]  * dataArray[ 9 ] * dataArray[ 14 ] + 
		dataArray[ 4 ]  * dataArray[ 10 ] * dataArray[ 13 ] +
		dataArray[ 8 ]  * dataArray[ 5 ]  * dataArray[ 14 ] - 
		dataArray[ 8 ]  * dataArray[ 6 ]  * dataArray[ 13 ] - 
		dataArray[ 12 ] * dataArray[ 5 ]  * dataArray[ 10 ] + 
		dataArray[ 12 ] * dataArray[ 6 ]  * dataArray[ 9 ];

	inv[ 1 ] = -dataArray[ 1 ]  * dataArray[ 10 ] * dataArray[ 15 ] + 
		dataArray[ 1 ]  * dataArray[ 11 ] * dataArray[ 14 ] + 
		dataArray[ 9 ]  * dataArray[ 2 ]  * dataArray[ 15 ] - 
		dataArray[ 9 ]  * dataArray[ 3 ]  * dataArray[ 14 ] - 
		dataArray[ 13 ] * dataArray[ 2 ]  * dataArray[ 11 ] + 
		dataArray[ 13 ] * dataArray[ 3 ]  * dataArray[ 10 ];

	inv[ 5 ] = dataArray[ 0 ]  * dataArray[ 10 ] * dataArray[ 15 ] - 
		dataArray[ 0 ]  * dataArray[ 11 ] * dataArray[ 14 ] - 
		dataArray[ 8 ]  * dataArray[ 2 ]  * dataArray[ 15 ] + 
		dataArray[ 8 ]  * dataArray[ 3 ]  * dataArray[ 14 ] + 
		dataArray[ 12 ] * dataArray[ 2 ]  * dataArray[ 11 ] - 
		dataArray[ 12 ] * dataArray[ 3 ]  * dataArray[ 10 ];

	inv[ 9 ] = -dataArray[ 0 ]  * dataArray[ 9 ] * dataArray[ 15 ] + 
		dataArray[ 0 ]  * dataArray[ 11 ] * dataArray[ 13 ] + 
		dataArray[ 8 ]  * dataArray[ 1 ]  * dataArray[ 15 ] - 
		dataArray[ 8 ]  * dataArray[ 3 ]  * dataArray[ 13 ] - 
		dataArray[ 12 ] * dataArray[ 1 ]  * dataArray[ 11 ] + 
		dataArray[ 12 ] * dataArray[ 3 ]  * dataArray[ 9 ];

	inv[ 13 ] = dataArray[ 0 ]  * dataArray[ 9 ] * dataArray[ 14 ] - 
		dataArray[ 0 ]  * dataArray[ 10 ] * dataArray[ 13 ] - 
		dataArray[ 8 ]  * dataArray[ 1 ]  * dataArray[ 14 ] + 
		dataArray[ 8 ]  * dataArray[ 2 ]  * dataArray[ 13 ] + 
		dataArray[ 12 ] * dataArray[ 1 ]  * dataArray[ 10 ] - 
		dataArray[ 12 ] * dataArray[ 2 ]  * dataArray[ 9 ];

	inv[ 2 ] = dataArray[ 1 ]  * dataArray[ 6 ] * dataArray[ 15 ] - 
		dataArray[ 1 ]  * dataArray[ 7 ] * dataArray[ 14 ] - 
		dataArray[ 5 ]  * dataArray[ 2 ] * dataArray[ 15 ] + 
		dataArray[ 5 ]  * dataArray[ 3 ] * dataArray[ 14 ] + 
		dataArray[ 13 ] * dataArray[ 2 ] * dataArray[ 7 ] - 
		dataArray[ 13 ] * dataArray[ 3 ] * dataArray[ 6 ];

	inv[ 6 ] = -dataArray[ 0]  * dataArray[ 6 ] * dataArray[ 15 ] + 
		dataArray[ 0 ]  * dataArray[ 7 ] * dataArray[ 14 ] + 
		dataArray[ 4 ]  * dataArray[ 2 ] * dataArray[ 15 ] - 
		dataArray[ 4 ]  * dataArray[ 3 ] * dataArray[ 14 ] - 
		dataArray[ 12 ] * dataArray[ 2 ] * dataArray[ 7 ] + 
		dataArray[ 12 ] * dataArray[ 3 ] * dataArray[ 6 ];

	inv[ 10 ] = dataArray[ 0 ]  * dataArray[ 5 ] * dataArray[ 15 ] - 
		dataArray[ 0 ]  * dataArray[ 7 ] * dataArray[ 13 ] - 
		dataArray[ 4 ]  * dataArray[ 1 ] * dataArray[ 15 ] + 
		dataArray[ 4 ]  * dataArray[ 3 ] * dataArray[ 13 ] + 
		dataArray[ 12 ] * dataArray[ 1 ] * dataArray[ 7 ] - 
		dataArray[ 12 ] * dataArray[ 3 ] * dataArray[ 5 ];

	inv[ 14 ] = -dataArray[ 0 ]  * dataArray[ 5 ] * dataArray[ 14 ] + 
		dataArray[ 0 ]  * dataArray[ 6 ] * dataArray[ 13 ] + 
		dataArray[ 4 ]  * dataArray[ 1 ] * dataArray[ 14 ] - 
		dataArray[ 4 ]  * dataArray[ 2 ] * dataArray[ 13 ] - 
		dataArray[ 12 ] * dataArray[ 1 ] * dataArray[ 6 ] + 
		dataArray[ 12 ] * dataArray[ 2 ] * dataArray[ 5 ];

	inv[ 3 ] = -dataArray[ 1 ] * dataArray[ 6 ] * dataArray[ 11 ] + 
		dataArray[ 1 ] * dataArray[ 7 ] * dataArray[ 10 ] + 
		dataArray[ 5 ] * dataArray[ 2 ] * dataArray[ 11 ] - 
		dataArray[ 5 ] * dataArray[ 3 ] * dataArray[ 10 ] - 
		dataArray[ 9 ] * dataArray[ 2 ] * dataArray[ 7 ] + 
		dataArray[ 9 ] * dataArray[ 3 ] * dataArray[ 6 ];

	inv[ 7 ] = dataArray[ 0 ] * dataArray[ 6 ] * dataArray[ 11 ] - 
		dataArray[ 0 ] * dataArray[ 7 ] * dataArray[ 10 ] - 
		dataArray[ 4 ] * dataArray[ 2 ] * dataArray[ 11 ] + 
		dataArray[ 4 ] * dataArray[ 3 ] * dataArray[ 10 ] + 
		dataArray[ 8 ] * dataArray[ 2 ] * dataArray[ 7 ] - 
		dataArray[ 8 ] * dataArray[ 3 ] * dataArray[ 6 ];

	inv[ 11 ] = -dataArray[ 0 ] * dataArray[ 5 ] * dataArray[ 11 ] + 
		dataArray[ 0 ] * dataArray[ 7 ] * dataArray[ 9 ] + 
		dataArray[ 4 ] * dataArray[ 1 ] * dataArray[ 11 ] - 
		dataArray[ 4 ] * dataArray[ 3 ] * dataArray[ 9 ] - 
		dataArray[ 8 ] * dataArray[ 1 ] * dataArray[ 7 ] + 
		dataArray[ 8 ] * dataArray[ 3 ] * dataArray[ 5 ];

	inv[ 15 ] = dataArray[ 0 ] * dataArray[ 5 ] * dataArray[ 10 ] - 
		dataArray[ 0 ] * dataArray[ 6 ] * dataArray[ 9 ] - 
		dataArray[ 4 ] * dataArray[ 1 ] * dataArray[ 10 ] + 
		dataArray[ 4 ] * dataArray[ 2 ] * dataArray[ 9 ] + 
		dataArray[ 8 ] * dataArray[ 1 ] * dataArray[ 6 ] - 
		dataArray[ 8 ] * dataArray[ 2 ] * dataArray[ 5 ];

	det = 1.0f / ( dataArray[ 0 ] * inv[ 0 ] + dataArray[ 1 ] * inv[ 4 ] + dataArray[ 2 ] * inv[ 8 ] + dataArray[ 3 ] * inv[ 12 ] );

	for( int i = 0; i < 16; ++i )
		toReturn.dataArray[ i ] = inv[ i ] * det;

	return toReturn;
}