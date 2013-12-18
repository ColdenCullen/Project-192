#ifndef __TRANSFORM
#define __TRANSFORM

// Includes
#include "btBulletDynamicsCommon.h"
#include "Quaternion.h"
#include "Vector3.h"
#include "Matrix4.h"

namespace Graphos
{
	namespace Physics
	{
		class GraphosMotionState;
	}
	namespace Math
	{
		struct Transform
		{
		public:
			Transform*				parent;

									Transform( void );
									~Transform( void );

			void					Rotate( const btQuaternion& rotation, bool global);
			void					Rotate( const gFloat x, const gFloat y, const gFloat z, const gFloat w, bool global );
			void					Rotate( const Vector3& eulerAngles );
			void					Rotate( const gFloat x, const gFloat y, const gFloat z );
			void					Translate( const Vector3& displacement );
			void					Translate( const gFloat x, const gFloat y, const gFloat z );
			void					TranslateTo( const Vector3& newLocation );
			void					TranslateTo( const gFloat x, const gFloat y, const gFloat z );
			void					Scale( const Vector3& scale );
			void					Scale( const gFloat x, const gFloat y, const gFloat z );

			const Math::Vector3*	Position( void )	const { return position; }
			const btQuaternion*		Rotation( void )	const { return rotation; }
			const Math::Vector3*	Scale( void )		const { return scale; }
			Math::Matrix4&			WorldMatrix( void );
			const Math::Matrix4		RotationMatrix( void ) const;

			const Math::Vector3*	GetRight( void )	const { return right; }
			const Math::Vector3*	GetUp( void )		const { return up; }
			const Math::Vector3*	GetForward( void )	const { return forward; }

			Math::Matrix4			ToRotationMatrix( const btQuaternion * quat ) const;

		private:
			Math::Matrix4			matrix;

			Math::Vector3*			position;
			btQuaternion*			rotation;
			Math::Vector3*			scale;

			Math::Vector3*			right;
			Math::Vector3*			up;
			Math::Vector3*			forward;
			

			void					UpdateLocalVectors( void );

			friend class			Graphos::Physics::GraphosMotionState;
		};
	}
}

#endif//__TRANSFORM