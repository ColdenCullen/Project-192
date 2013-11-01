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
			static void			Initialize( void );
			static void			Shutdown( void );

			static void			AddCollider( Collider* col );
			static void			Update( void );

			static Math::Vector3 gravity;

		private:
			struct Simplex
			{
			public:
				Simplex( void ) : size( 0 ) { }

				Math::Vector3
								points[ 4 ];
				unsigned char	size;

				/*const*/ Math::Vector3&
								GetLast( void );// const;
				void			Add( const Math::Vector3& newPoint );
				void			Remove( const Math::Vector3& target );
				bool			ContainsOrigin( Math::Vector3& direction );
			};

								Physics( void ) { }
								Physics( const Physics& );
			void				operator=( const Physics& );

			// Get point in Minkowski Difference furthest in direction
			static Math::Vector3 Support( Collider* shape1, Collider* shape2, Math::Vector3& direction );

			static bool			CheckGJK( Collider* shape1, Collider* shape2 );

			static std::vector<Collider*> colliders;
		};
	}
}

#endif//_PHYSICS_H_