#ifndef _VECTOR2_H_
#define _VECTOR2_H_

namespace Graphos
{
	namespace Math
	{
		struct Vector2
		{
		public:
			Vector2( const float values[ 2 ] ) : x( values[ 0 ] ), y( values[ 1 ] ) { }
			Vector2( float x = 0.0f, float y = 0.0f ) : x( x ), y( y ) { }
			Vector2( const Vector2& other ) : x( other.x ), y( other.y ) { }

			float operator[]( const int index ) const
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
			float Cross( const Vector2& other ) const
			{
				return ( x * other.y ) - ( y * other.x );
			}
			// Cross product
			float operator%( const Vector2& other ) const
			{
				return Cross( other );
			}

			// Dot product
			float Dot( const Vector2& other ) const
			{
				return ( x * other.x ) + ( y * other.y );
			}
			// Dot product
			float operator*( const Vector2& other ) const
			{
				return Dot( other );
			}

			// Multiply by scaler
			Vector2 operator*( const float other ) const
			{
				return Vector2( x * other, y * other );
			}

			// Conversion function
			operator float()
			{
				return Magnitude();
			}

			// Magnitude
			float Magnitude( void ) const
			{
				return sqrt( ( x * x ) + ( y * y ) );
			}

			Vector2 Normalize( void ) const
			{
				float mag = sqrt( ( x * x ) + ( y * y ) );

				return Vector2( x / mag, y / mag );
			}
			
			float x, y;
		};
	}
}

#endif // _VECTOR2_H_