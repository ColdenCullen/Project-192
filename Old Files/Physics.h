#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include <vector>

#include "Vector3.h"
#include "Collider.h"

using namespace Graphos::Math;

namespace Graphos
{
	class Physics
	{
	public:
		bool				Initialize( void );
		void				Shutdown( void );

		void				AddCollider( Collider* col );
		void				Update( void );

		static Physics&		Get( void )
		{
			static Physics instance;
			return instance;
		}

		Vector3				gravity;

	private:
		struct Simplex
		{
		public:
			Simplex( void ) : size( 0 ) { }

			Vector3			points[ 4 ];
			unsigned char	size;

			/*const*/ Vector3&	GetLast( void );// const;
			void			Add( const Vector3& newPoint );
			void			Remove( const Vector3& target );
			bool			ContainsOrigin( Vector3& direction );
		};

							Physics( void );
							Physics( const Physics& );
		void				operator=( const Physics& );

		// Get point in Minkowski Difference furthest in direction
		Vector3				Support( Collider* shape1, Collider* shape2, Vector3& direction );

		bool				CheckGJK( Collider* shape1, Collider* shape2 );

		vector<Collider*>	colliders;
	};
}

#endif//_PHYSICS_H_