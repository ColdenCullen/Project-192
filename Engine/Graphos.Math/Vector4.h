#ifndef _VECTOR4_H_
#define _VECTOR4_H_

#include <math.h>

namespace Graphos
{
	namespace Math
	{
		struct Vector4
		{
		public:
			#pragma region Statics
			const static Vector4 Zero;
			const static Vector4 Right;
			const static Vector4 Up;
			const static Vector4 Forward;
			#pragma endregion
			
			Vector4( const float values[ 4 ] ) : x( values[ 0 ] ), y( values[ 1 ] ), z( values[ 2 ] ), w( values[ 3 ] ) { }
			Vector4( float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f ) : x( x ), y( y ), z( z ), w( w ) { }
			Vector4( const Vector4& other ) : x( other.x ), y( other.y ), z( other.z ), w( other.w ) { }

			float operator[]( const int index ) const
			{
				return *( &x + index );
			}

			Vector4& operator=( const Vector4& other )
			{
				if( &other != this )
				{
					x = other.x;
					y = other.y;
					z = other.z;
					w = other.w;
				}

				return *this;
			}

			inline bool Equals( const Vector4& other ) const
			{
				return x == other.x && y == other.y && z == other.z && w == other.w;
			}

			inline bool operator==( const Vector4& other ) const
			{
				return Equals( other );
			}

			// Arithmetic
			inline Vector4 Add( const Vector4& other ) const
			{
				return Vector4( x + other.x, y + other.y, z + other.z, w + other.w );
			}

			inline Vector4 operator+( const Vector4& other ) const
			{
				return Add( other );
			}

			Vector4& operator+=( const Vector4& other )
			{
				x += other.x;
				y += other.y;
				z += other.z;
				w += other.w;

				return *this;
			}

			inline Vector4 operator-( const Vector4& other ) const
			{
				return Vector4( x - other.x, y - other.y, z - other.z, w - other.w );
			}

			Vector4& operator-=( const Vector4& other )
			{
				x -= other.x;
				y -= other.y;
				z -= other.z;
				w -= other.w;

				return *this;
			}
			
			// Inverse
			inline Vector4 Inverse( void ) const
			{
				return Vector4( -x, -y, -z, -w );
			}
			// Inverse
			inline Vector4 operator-( void ) const
			{
				return Vector4( -x, -y, -z, -w );
			}

			// Rotate
			inline Vector4 Rotate( const float xDeg, const float yDeg, const float zDeg, const float wDeg )
			{
				return Vector4( x * cos( zDeg ) - y * sin( zDeg ), x * sin( zDeg ) - y * cos( zDeg ), z, w );
			}

			// Dot product
			inline float Dot( const Vector4& other ) const
			{
				return ( x * other.x ) + ( y * other.y ) + ( z * other.z ) + ( w * other.w );
			}
			// Dot product
			inline float operator*( const Vector4& other ) const
			{
				return Dot( other );
			}

			// Multiply by scaler
			inline Vector4 operator*( const float other ) const
			{
				return Vector4( x * other, y * other, z * other, w * other );
			}
			// Multiply by scaler
			Vector4& operator*=( const float other )
			{
				x *= other;
				y *= other;
				z *= other;
				w *= other;

				return *this;
			}

			// Divide by scalar
			inline Vector4 operator/( const float other ) const
			{
				return Vector4( x / other, y / other, z / other, w / other );
			}
			Vector4& operator/=( const float other )
			{
				x /= other;
				y /= other;
				z /= other;
				w /= other;

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
				return sqrt( ( x * x ) + ( y * y ) + ( z * z ) + ( w * w ) );
			}

			// Normalize
			Vector4 Normalize( void ) const
			{
				float mag = Magnitude();

				return Vector4( x / mag, y / mag, z / mag, w / mag );
			}

			union
			{
				struct 
				{
					float x, y, z, w;
				};
				struct 
				{
					float r, g, b, a;
				};
			};
		};
	}
}

#endif //_VECTOR4_H_