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
			Matrix4( gFloat val00, gFloat val01, gFloat val02, gFloat val03,
					gFloat val10, gFloat val11, gFloat val12, gFloat val13,
					gFloat val20, gFloat val21, gFloat val22, gFloat val23,
					gFloat val30, gFloat val31, gFloat val32, gFloat val33 )
			{
				dataArray[ 0 ] = val00; dataArray[ 1 ] = val01; dataArray[ 2 ] = val02; dataArray[ 3 ] = val03;
				dataArray[ 4 ] = val10; dataArray[ 5 ] = val11; dataArray[ 6 ] = val12; dataArray[ 7 ] = val13;
				dataArray[ 8 ] = val20; dataArray[ 9 ] = val21; dataArray[ 10 ] = val22; dataArray[ 11 ] = val23;
				dataArray[ 12 ] = val30; dataArray[ 13 ] = val31; dataArray[ 14 ] = val32; dataArray[ 15 ] = val33;
			}

			Matrix4				operator*( const Matrix4& other ) const;
			Matrix4				Mul( const Matrix4& other ) const;

			Matrix4				operator+( const Matrix4& other ) const;
			Matrix4				Add( const Matrix4& other ) const;

			Matrix4&			operator*=( const Matrix4& other );

			Matrix4&			operator+=( const Matrix4& other );

			bool				operator==( const Matrix4& other ) const;
			bool				Equals( const Matrix4& other ) const;

			Matrix4				Inverse( void ) const;
			Matrix4				Transpose( void ) const;

			Vector3				operator*( const Vector3& vec ) const;
			Vector3				Mul( const Vector3& vec ) const;

			static Matrix4		BuildPerspective( const gFloat fov, const gFloat screenAspect, const gFloat near, const gFloat depth );
			static Matrix4		BuildOrthogonal( const gFloat width, const gFloat height, const gFloat near, const gFloat far );

			static const Matrix4 Identity;

			union
			{
				gFloat matrix[ WIDTH ][ WIDTH ];
				gFloat dataArray[ WIDTH * WIDTH ];
			};
		};
	}
}

#endif //_MATRIX4_H_