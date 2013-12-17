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
			
			Vector4( const gFloat values[ 4 ] ) : x( values[ 0 ] ), y( values[ 1 ] ), z( values[ 2 ] ), w( values[ 3 ] ) { }
			Vector4( gFloat x = 0.0f, gFloat y = 0.0f, gFloat z = 0.0f, gFloat w = 0.0f ) : x( x ), y( y ), z( z ), w( w ) { }
			Vector4( gFloat value ) : x( value ), y( value ), z( value ), w( value ) { }
			Vector4( const Vector4& other ) : x( other.x ), y( other.y ), z( other.z ), w( other.w ) { }

			gFloat operator[]( const int index ) const
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
			inline Vector4 Rotate( const gFloat xDeg, const gFloat yDeg, const gFloat zDeg, const gFloat wDeg )
			{
				return Vector4( x * cos( zDeg ) - y * sin( zDeg ), x * sin( zDeg ) - y * cos( zDeg ), z, w );
			}

			// Dot product
			inline gFloat Dot( const Vector4& other ) const
			{
				return ( x * other.x ) + ( y * other.y ) + ( z * other.z ) + ( w * other.w );
			}
			// Dot product
			inline gFloat operator*( const Vector4& other ) const
			{
				return Dot( other );
			}

			// Multiply by scaler
			inline Vector4 operator*( const gFloat other ) const
			{
				return Vector4( x * other, y * other, z * other, w * other );
			}
			// Multiply by scaler
			Vector4& operator*=( const gFloat other )
			{
				x *= other;
				y *= other;
				z *= other;
				w *= other;

				return *this;
			}

			// Divide by scalar
			inline Vector4 operator/( const gFloat other ) const
			{
				return Vector4( x / other, y / other, z / other, w / other );
			}
			Vector4& operator/=( const gFloat other )
			{
				x /= other;
				y /= other;
				z /= other;
				w /= other;

				return *this;
			}

			// Conversion function
			operator gFloat()
			{
				return Magnitude();
			}
			
			// Magnitude
			inline gFloat Magnitude( void ) const
			{
				return sqrt( ( x * x ) + ( y * y ) + ( z * z ) + ( w * w ) );
			}

			// Normalize
			Vector4 Normalize( void ) const
			{
				gFloat mag = Magnitude();

				return Vector4( x / mag, y / mag, z / mag, w / mag );
			}

			union
			{
				struct 
				{
					gFloat x, y, z, w;
				};
				struct 
				{
					gFloat r, g, b, a;
				};
			};
		};
	}
}

#endif //_VECTOR4_H_