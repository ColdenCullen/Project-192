#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include <vector>

#include "Vector3.h"
#include "Collider.h"
#include "IController.h"
#include "ISingleton.h"

namespace Graphos
{
	namespace Physics
	{
		class Physics : public Core::IController
		{
		public:
			virtual void		Initialize( void ) override;
			virtual void		Shutdown( void ) override;

			void				AddCollider( Collider* col );
			void				Update( void );

			Math::Vector3
								gravity;

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

			Physics( void );
			Physics( const Physics& );
			void				operator=( const Physics& );

			// Get point in Minkowski Difference furthest in direction
			Math::Vector3		Support( Collider* shape1, Collider* shape2, Math::Vector3& direction );

			bool				CheckGJK( Collider* shape1, Collider* shape2 );

			std::vector<Collider*>
								colliders;

			friend class		Core::ISingleton<Physics>;
		};
	}
}

#endif//_PHYSICS_H_