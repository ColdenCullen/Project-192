#ifndef __TRANSFORM
#define __TRANSFORM

// Includes
#include "Quaternion.h"
#include "Vector3.h"
#include "Matrix4.h"

using namespace Graphos::Math;

namespace Graphos
{
	namespace Math
	{
		struct Transform
		{
		public:
			Transform*				parent;

									Transform( void );

			void					Rotate( Quaternion rotation );
			void					Rotate( const float x, const float y, const float z, const float w );
			void					Rotate( const Vector3& eulerAngles );
			void					Rotate( const float x, const float y, const float z );
			void					Translate( const Vector3& displacement );
			void					Translate( const float x, const float y, const float z );
			void					Scale( const Vector3& scale );
			void					Scale( const float x, const float y, const float z );

			const Vector3&			Position( void )	const { return position; }
			const Vector3&			Rotation( void )	const { return rotation; }
			const Vector3&			Scale( void )		const { return scale; }
			const Matrix4			WorldMatrix( void )	const;
			const Matrix4			RotationMatrix( void ) const;

			const Vector3&			GetRight( void )	const { return right; }
			const Vector3&			GetUp( void )		const { return up; }
			const Vector3&			GetForward( void )	const { return forward; }

		private:
			Matrix4					matrix;

			Vector3					position;
			Vector3					rotation;
			Vector3					scale;

			Vector3					right;
			Vector3					up;
			Vector3					forward;

			Matrix4					RotateX( const float angle ) const;
			Matrix4					RotateY( const float angle ) const;
			Matrix4					RotateZ( const float angle ) const;

			void					UpdateLocalVectors( void );
		};
	}
}

#endif//__TRANSFORM