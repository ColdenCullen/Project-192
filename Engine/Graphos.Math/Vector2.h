#ifndef _VECTOR2_H_
#define _VECTOR2_H_

namespace Graphos
{
	namespace Math
	{
		struct Vector2
		{
		public:
			Vector2( const gFloat values[ 2 ] ) : x( values[ 0 ] ), y( values[ 1 ] ) { }
			Vector2( gFloat x = 0.0f, gFloat y = 0.0f ) : x( x ), y( y ) { }
			Vector2( const Vector2& other ) : x( other.x ), y( other.y ) { }
			Vector2( gFloat value ) : x( value ), y( value ) { }

			gFloat operator[]( const int index ) const
			{
				return *( &x + index );
			}

			Vector2& operator=( const Vector2& other )
			{
				if( &other != this )
				{
					x = other.x;
					y = other.y;
				}

				return *this;
			}

			// Arithmetic
			Vector2 operator+( const Vector2& other ) const
			{
				return Vector2( x + other.x, y + other.y );
			}

			Vector2 operator-( const Vector2& other ) const
			{
				return Vector2( x - other.x, y - other.y );
			}

			Vector2 operator-=( const Vector2& other )
			{
				x -= other.x;
				y -= other.y;

				return *this;
			}

			// Cross product
			gFloat Cross( const Vector2& other ) const
			{
				return ( x * other.y ) - ( y * other.x );
			}
			// Cross product
			gFloat operator%( const Vector2& other ) const
			{
				return Cross( other );
			}

			// Dot product
			gFloat Dot( const Vector2& other ) const
			{
				return ( x * other.x ) + ( y * other.y );
			}
			// Dot product
			gFloat operator*( const Vector2& other ) const
			{
				return Dot( other );
			}

			// Multiply by scaler
			Vector2 operator*( const gFloat other ) const
			{
				return Vector2( x * other, y * other );
			}

			// Conversion function
			operator gFloat()
			{
				return Magnitude();
			}

			// Magnitude
			gFloat Magnitude( void ) const
			{
				return sqrt( ( x * x ) + ( y * y ) );
			}

			Vector2 Normalize( void ) const
			{
				gFloat mag = sqrt( ( x * x ) + ( y * y ) );

				return Vector2( x / mag, y / mag );
			}
			
			gFloat x, y;
		};
	}
}

#endif // _VECTOR2_H_