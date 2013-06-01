#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include "Vector3.h"

#define WIDTH 4

namespace Graphos
{
	namespace Math
	{
		//template<unsigned int HEIGHT = 4>
		struct Matrix4
		{
		public:
			Matrix4( void ) { }
			Matrix4( float val00, float val01, float val02, float val03,
					float val10, float val11, float val12, float val13,
					float val20, float val21, float val22, float val23,
					float val30, float val31, float val32, float val33 )
			{
				dataArray[ 0 ] = val00; dataArray[ 1 ] = val01; dataArray[ 2 ] = val02; dataArray[ 3 ] = val03;
				dataArray[ 4 ] = val10; dataArray[ 5 ] = val11; dataArray[ 6 ] = val12; dataArray[ 7 ] = val13;
				dataArray[ 8 ] = val20; dataArray[ 9 ] = val21; dataArray[ 10 ] = val22; dataArray[ 11 ] = val23;
				dataArray[ 12 ] = val30; dataArray[ 13 ] = val31; dataArray[ 14 ] = val32; dataArray[ 15 ] = val33;
			}

			Matrix4				operator*( const Matrix4& other ) const;

			Matrix4				operator+( const Matrix4& other ) const;

			Matrix4&			operator*=( const Matrix4& other );

			Matrix4&			operator+=( const Matrix4& other );

			bool				operator==( const Matrix4& other ) const;

			Matrix4				Inverse( void ) const;

			Vector3				operator*( const Vector3& vec ) const;

			static Matrix4		BuildPerspective( const float fov, const float screenAspect, const float near, const float depth );
			static Matrix4		BuildOrthogonal( const float width, const float height, const float near, const float far );

			static const Matrix4 Identity;

			union
			{
				float matrix[ WIDTH ][ WIDTH ];
				float dataArray[ WIDTH * WIDTH ];
			};
		};
	}
}

#endif //_MATRIX4_H_