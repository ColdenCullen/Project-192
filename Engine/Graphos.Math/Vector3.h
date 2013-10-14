#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <math.h>

namespace Graphos
{
	namespace Math
	{
		struct Vector3
		{
		public:
			#pragma region Statics
			const static Vector3 Zero;
			const static Vector3 Right;
			const static Vector3 Up;
			const static Vector3 Forward;
			static Vector3 TripleProduct( const Vector3& a, const Vector3& b, const Vector3& c )
			{
				//return ( b * a.Dot( c ) ) - ( a * b.Dot( c ) );

				float z = ( a.x * b.y ) - ( a.y * b.x );
				return Vector3( -z * c.y, z * c.x, 0.0f );
			}
			#pragma endregion

			Vector3( const float values[ 3 ] ) : x( values[ 0 ] ), y( values[ 1 ] ), z( values[ 2 ] ) { }
			Vector3( float x = 0.0f, float y = 0.0f, float z = 0.0f ) : x( x ), y( y ), z( z ) { }
			Vector3( const Vector3& other ) : x( other.x ), y( other.y ), z( other.z ) { }

			float operator[]( const int index ) const
			{
				return *( &x + index );
			}

			Vector3& operator=( const Vector3& other )
			{
				if( &other != this )
				{
					x = other.x;
					y = other.y;
					z = other.z;
				}

				return *this;
			}

			inline bool Equals( const Vector3& other ) const
			{
				return x == other.x && y == other.y && z == other.z;
			}

			inline bool operator==( const Vector3& other ) const
			{
				return Equals( other );
			}

			// Arithmetic
			inline Vector3 Add( const Vector3& other ) const
			{
				return Vector3( x + other.x, y + other.y, z + other.z );
			}

			inline Vector3 operator+( const Vector3& other ) const
			{
				return Add( other );
			}

			Vector3& operator+=( const Vector3& other )
			{
				x += other.x;
				y += other.y;
				z += other.z;

				return *this;
			}

			inline Vector3 operator-( const Vector3& other ) const
			{
				return Vector3( x - other.x, y - other.y, z - other.z );
			}

			Vector3& operator-=( const Vector3& other )
			{
				x -= other.x;
				y -= other.y;
				z -= other.z;

				return *this;
			}
			
			inline Vector3 operator-( float other ) const
			{
				return Vector3( x - other, y - other, z - other );
			}

			Vector3& operator-=( float other )
			{
				x -= other;
				y -= other;
				z -= other;

				return *this;
			}

			// Inverse
			inline Vector3 Inverse( void ) const
			{
				return Vector3( -x, -y, -z );
			}
			// Inverse
			inline Vector3 operator-( void ) const
			{
				return Vector3( -x, -y, -z );
			}

			// Rotate
			inline Vector3 Rotate( const float xDeg, const float yDeg, const float zDeg )
			{
				return Vector3( x * cos( zDeg ) - y * sin( zDeg ), x * sin( zDeg ) - y * cos( zDeg ), z );
			}

			// Dot product
			inline float Dot( const Vector3& other ) const
			{
				return ( x * other.x ) + ( y * other.y ) + ( z * other.z );
			}
			// Dot product
			inline float operator*( const Vector3& other ) const
			{
				return Dot( other );
			}

			// Cross product
			inline Vector3 Cross( const Vector3& other ) const
			{
				return Vector3( ( y * other.z ) - ( z * other.y ), ( z * other.x ) - ( x * other.z ), ( x * other.y ) - ( y * other.x ) );
			}
			// Cross product
			inline Vector3 operator%( const Vector3& other ) const
			{
				return Vector3( ( y * other.z ) - ( z * other.y ), ( x * other.z ) - ( z * other.x ), ( x * other.y ) - ( y * other.x ) );
			}

			// Multiply by scaler
			inline Vector3 operator*( const float other ) const
			{
				return Vector3( x * other, y * other, z * other );
			}
			// Multiply by scaler
			Vector3& operator*=( const float other )
			{
				x *= other;
				y *= other;
				z *= other;

				return *this;
			}

			// Divide by scalar
			inline Vector3 operator/( const float other ) const
			{
				return Vector3( x / other, y / other, z / other );
			}
			Vector3& operator/=( const float other )
			{
				x /= other;
				y /= other;
				z /= other;

				return *this;
			}

			// Conversion function
			operator float()
			{
				return Magnitude();
			}
			
			// Magnitude
			inline float Magnitude( void ) const
			{
				return sqrt( ( x * x ) + ( y * y ) + ( z * z ) );
			}

			// Normalize
			Vector3 Normalize( void ) const
			{
				float mag = Magnitude();

				return Vector3( x / mag, y / mag, z / mag );
			}

			union
			{
				struct 
				{
					float x, y, z;
				};
				struct 
				{
					float r, g, b;
				};
			};
		};
	}
}

#endif //_VECTOR3_H_