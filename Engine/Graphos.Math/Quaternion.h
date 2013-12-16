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
			gFloat w;

			// Angular component
			union
			{
				// Vector version
				struct { Vector3 axis; };

				// gFloat version
				struct { gFloat x, y, z; };
			};

			// Constructors
			Quaternion( void ) : axis(), w( 1.0f ) { };
			Quaternion( const Vector3& axis, const gFloat angle )
			{
				const gFloat fHalfAngle = 0.5f * angle;
				const gFloat fSin = sinf( fHalfAngle );
				w = cosf( fHalfAngle );
				x = fSin * axis.x;
				y = fSin * axis.y;
				z = fSin * axis.z;
			}
			Quaternion( const gFloat x, const gFloat y, const gFloat z, const gFloat w )
			{
				const gFloat fHalfAngle = 0.5f * w;
				const gFloat fSin = sinf( fHalfAngle );
				this->w = cosf( fHalfAngle );
				this->x = fSin * x;
				this->y = fSin * y;
				this->z = fSin * z;
			}
			Quaternion( const Quaternion& other ) : axis( other.axis ), w( other.w ) { }

			/**
			 * @fn	Quaternion& Lerp( const Quaternion& q1, const Quaternion& q2, gFloat time)
			 *
			 * @brief	Lerps a quaternion.
			 *
			 * @author	Colden Cullen
			 * @date	12/8/2013
			 *
			 * @param	q1  	The first Quaternion.
			 * @param	q2  	The second Quaternion.
			 * @param	time	The time.
			 *
			 * @return	A Quaternion.
			 */
			Quaternion& Lerp( const Quaternion& q1, gFloat time)
			{
				const gFloat scale = 1.0f - time;
				return ( *this * scale ) + ( q1 * time );
			}

			/**
			 * @fn	gBool operator==( const Quaternion& other ) const
			 *
			 * @brief	Equality operator.
			 *
			 * @author	Colden Cullen
			 * @date	12/8/2013
			 *
			 * @param	other	The other.
			 *
			 * @return	true if the parameters are considered equivalent.
			 */
			gBool operator==( const Quaternion& other ) const
			{
				return axis == other.axis && w == other.w;
			}

			/**
			 * @fn	Quaternion operator+( const Quaternion& other ) const
			 *
			 * @brief	Addition operator.
			 *
			 * @author	Colden Cullen
			 * @date	12/8/2013
			 *
			 * @param	other	The other.
			 *
			 * @return	The result of the operation.
			 */
			Quaternion operator+( const Quaternion& other ) const
			{
				return Quaternion( axis + other.axis, w + other.w );
			}

			/**
			 * @fn	Quaternion operator*( const gFloat lin ) const
			 *
			 * @brief	Multiplies a quaternion by a linear value.
			 *
			 * @author	Colden Cullen
			 * @date	12/8/2013
			 *
			 * @param	lin	The linear value.
			 *
			 * @return	The result of the operation.
			 */
			Quaternion operator*( const gFloat lin ) const
			{
				return Quaternion( axis * lin, w * lin );
			}

			/**
			 * @fn	Quaternion operator*( const Quaternion& other ) const
			 *
			 * @brief	Multiply quaternions.
			 *
			 * @author	Colden Cullen
			 * @date	12/8/2013
			 *
			 * @param	other	The other.
			 *
			 * @return	The result of the operation.
			 */
			Quaternion operator*( const Quaternion& other ) const
			{
				/*
				return Quaternion(
					x * other.w + y * other.z - z * other.y + w * other.x,
					-x * other.z + y * other.w + z * other.x + w * other.y,
					x * other.y - y * other.x + z * other.w + w * other.z,
					-x * other.x - y * other.y - z * other.z + w * other.w
				);
				*/
				return Quaternion(
					other.w * x + other.x * w + other.y * z - other.z * y,
					other.w * y - other.x * z + other.y * w + other.z * x,
					other.w * z + other.x * y - other.y * x + other.z * w,
					other.w * w - other.x * x - other.y * y - other.z * z
					);
			}

			/**
			 * @fn	Quaternion& operator*=( const Quaternion& other )
			 *
			 * @brief	Multiplication assignment operator.
			 *
			 * @author	Colden Cullen
			 * @date	12/8/2013
			 *
			 * @param	other	The other.
			 *
			 * @return	The result of the operation.
			 */
			Quaternion& operator*=( const Quaternion& other )
			{
				/*
				x = x * other.w + y * other.z - z * other.y + w * other.x;
				y = -x * other.z + y * other.w + z * other.x + w * other.y;
				z = x * other.y - y * other.x + z * other.w + w * other.z;
				w = -x * other.x - y * other.y - z * other.z + w * other.w;
				*/

				x = other.w * x + other.x * w + other.y * z - other.z * y;
				y = other.w * y - other.x * z + other.y * w + other.z * x;
				z = other.w * z + other.x * y - other.y * x + other.z * w;
				w = other.w * w - other.x * x - other.y * y - other.z * z;

				return *this;
			}

			/**
			 * @fn	Matrix4 ToRotationMatrix( void ) const
			 *
			 * @brief	Convert to multiply-able rotation matrix.
			 * 			Help from http://stackoverflow.com/questions/1556260/convert-quaternion-rotation-to-rotation-matrix
			 *
			 * @author	Colden Cullen
			 * @date	12/8/2013
			 *
			 * @return	This object as a Matrix4.
			 */
			Matrix4 ToRotationMatrix( void ) const
			{
				return Matrix4(
					1.0f - 2.0f * y * y - 2.0f * z * z, 2.0f * x * y - 2.0f * z * w, 2.0f * x * z + 2.0f * y * w, 0.0f,
					2.0f * x * y + 2.0f * z * w, 1.0f - 2.0f * x * x - 2.0f * z * z, 2.0f * y * z - 2.0f * x * w, 0.0f,
					2.0f * x * z - 2.0f * y * w, 2.0f * y * z + 2.0f * x * w, 1.0f - 2.0f * x * x - 2.0f * y * y, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f
				);
			}
		};
	}
}

#endif//__QUATERNION