#ifndef __TRANSFORM
#define __TRANSFORM

// Includes
#include "Quaternion.h"
#include "Vector3.h"
#include "Matrix4.h"

namespace Graphos
{
	namespace Math
	{
		struct Transform
		{
		public:
			Transform*				parent;

									Transform( void );
									~Transform( void );

			void					Rotate( const Quaternion& rotation );
			void					Rotate( const float x, const float y, const float z, const float w );
			void					Rotate( const Vector3& eulerAngles );
			void					Rotate( const float x, const float y, const float z );
			void					Translate( const Vector3& displacement );
			void					Translate( const float x, const float y, const float z );
			void					Scale( const Vector3& scale );
			void					Scale( const float x, const float y, const float z );

			const Math::Vector3*	Position( void )	const { return position; }
			const Math::Vector3*	Rotation( void )	const { return rotation; }
			const Math::Vector3*	Scale( void )		const { return scale; }
			const Math::Matrix4		WorldMatrix( void )	const;
			const Math::Matrix4		RotationMatrix( void ) const;

			const Math::Vector3*	GetRight( void )	const { return right; }
			const Math::Vector3*	GetUp( void )		const { return up; }
			const Math::Vector3*	GetForward( void )	const { return forward; }

		private:
			Math::Matrix4			matrix;

			Math::Vector3*			position;
			Math::Vector3*			rotation;
			Math::Vector3*			scale;

			Math::Vector3*			right;
			Math::Vector3*			up;
			Math::Vector3*			forward;

			Math::Matrix4			RotateX( const float angle ) const;
			Math::Matrix4			RotateY( const float angle ) const;
			Math::Matrix4			RotateZ( const float angle ) const;

			void					UpdateLocalVectors( void );
		};
	}
}

#endif//__TRANSFORM