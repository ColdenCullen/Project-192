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

		private:
			Matrix4					matrix;

			Vector3					position;
			Vector3					rotation;
			Vector3					scale;

			Matrix4					RotateX( const float angle ) const;
			Matrix4					RotateY( const float angle ) const;
			Matrix4					RotateZ( const float angle ) const;
		};
	}
}

#endif//__TRANSFORM