#ifndef __GRAPHOS_BEHAVIOR
#define __GRAPHOS_BEHAVIOR

#include "IComponent.h"
#include "GameObject.h"

namespace Graphos
{
	namespace Core
	{
		class GraphosBehavior : public IComponent
		{
		public:
								GraphosBehavior( GameObject* owner ) : IComponent( owner ) { }

			void				Initialize( void ) { }
			void				Update( void ) { }
			void				Draw( void ) { }
			void				Shutdown( void ) { }
		};
	}
}

#endif//__GRAPHOS_BEHAVIOR
