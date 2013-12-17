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
			void					Rotate( const gFloat x, const gFloat y, const gFloat z, const gFloat w );
			void					Rotate( const Vector3& eulerAngles );
			void					Rotate( const gFloat x, const gFloat y, const gFloat z );
			void					Translate( const Vector3& displacement );
			void					Translate( const gFloat x, const gFloat y, const gFloat z );
			void					TranslateTo( const Vector3& newLocation );
			void					TranslateTo( const gFloat x, const gFloat y, const gFloat z );
			void					Scale( const Vector3& scale );
			void					Scale( const gFloat x, const gFloat y, const gFloat z );

			void					Pitch( const gFloat angle );
			void					Yaw( const gFloat angle );
			void					Roll( const gFloat angle );

			const Math::Vector3*	Position( void )	const { return position; }
			const Math::Quaternion*	Rotation( void )	const { return rotation; }
			const Math::Vector3*	Scale( void )		const { return scale; }
			Math::Matrix4&			WorldMatrix( void );
			const Math::Matrix4		RotationMatrix( void ) const;

			const Math::Vector3*	GetRight( void )	const { return right; }
			const Math::Vector3*	GetUp( void )		const { return up; }
			const Math::Vector3*	GetForward( void )	const { return forward; }

		private:
			Math::Matrix4			matrix;

			Math::Vector3*			position;
			Math::Quaternion*		rotation;
			Math::Vector3*			scale;

			Math::Vector3*			right;
			Math::Vector3*			up;
			Math::Vector3*			forward;

			void					UpdateLocalVectors( void );
		};
	}
}

#endif//__TRANSFORM