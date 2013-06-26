#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include <vector>

#include "Vector3.h"
#include "Collider.h"

namespace Graphos
{
	namespace Physics
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

			Graphos::Math::Vector3
								gravity;

		private:
			struct Simplex
			{
			public:
				Simplex( void ) : size( 0 ) { }

				Graphos::Math::Vector3
								points[ 4 ];
				unsigned char	size;

				/*const*/ Graphos::Math::Vector3&
								GetLast( void );// const;
				void			Add( const Graphos::Math::Vector3& newPoint );
				void			Remove( const Graphos::Math::Vector3& target );
				bool			ContainsOrigin( Graphos::Math::Vector3& direction );
			};

			Physics( void );
			Physics( const Physics& );
			void				operator=( const Physics& );

			// Get point in Minkowski Difference furthest in direction
			Vector3				Support( Collider* shape1, Collider* shape2, Graphos::Math::Vector3& direction );

			bool				CheckGJK( Collider* shape1, Collider* shape2 );

			std::vector<Collider*>
								colliders;
		};
	}
}

#endif//_PHYSICS_H_