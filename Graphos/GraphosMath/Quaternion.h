#ifndef __QUATERNION
#define __QUATERNION

#include "Vector3.h"
#include "Matrix4.h"

namespace Graphos
{
	namespace Math
	{
		struct Quaternion
		{
		public:
			// Multiplication identity
			static const Quaternion Identity;

			// Scaler component
			float w;

			// Angular component
			union
			{
				// Vector version
				struct { Vector3 axis; };

				// Float version
				struct { float x, y, z; };
			};

			// Constructors
			Quaternion( void ) : axis(), w( 1.0f ) { };
			Quaternion( const Vector3& axisOther, const float w ) : axis( axisOther ), w( w ) { }
			Quaternion( const float x, const float y, const float z, const float w ) : axis( x, y, z ), w( w ) { }
			Quaternion( const Quaternion& other ) : axis( other.axis ), w( other.w ) { }
			
			// Multiply quaternions
			Quaternion operator*( const Quaternion& other ) const
			{
				return Quaternion(
					x * other.w + y * other.z - z * other.y + w * other.x,
					-x * other.z + y * other.w + z * other.x + w * other.y,
					x * other.y - y * other.x + z * other.w + w * other.z,
					-x * other.x - y * other.y - z * other.z + w * other.w
				);
			}
			Quaternion& operator*=( const Quaternion& other )
			{
				x = x * other.w + y * other.z - z * other.y + w * other.x;
				y = -x * other.z + y * other.w + z * other.x + w * other.y;
				z = x * other.y - y * other.x + z * other.w + w * other.z;
				w = -x * other.x - y * other.y - z * other.z + w * other.w;

				return *this;
			}

			// Convert to multiply-able rotation matrix
			Matrix4 ToRotationMatrix( void ) const
			{
				return Matrix4(
					1 - 2 * ( pow( y, 2.0f ) - pow( z, 2.0f ) ), 2 * ( x * y + z * w ), 2 * ( x * z - y * w ), 0.0f,
					2 * ( x * y - z * w ), 1 - 2 * ( pow( x, 2.0f ) - pow( z, 2.0f ) ), 2 * ( y * z + x * w ), 0.0f,
					2 * ( x * z + y * w ), 2 * ( y * z - x * w ), 1 - 2 * ( pow( x, 2.0f ) - pow( y, 2.0f ) ), 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f
				);
			}
		};
	}
}

#endif//__QUATERNION