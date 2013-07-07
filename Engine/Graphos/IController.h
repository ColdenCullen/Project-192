#ifndef __INGREDIENT_CONTROLLER
#define __INGREDIENT_CONTROLLER

namespace Graphos
{
	namespace Core
	{
		class IController
		{
		public:
			virtual void		Initialize( void ) = 0;
			virtual void		Shutdown( void ) = 0;
		};
	}
}

#endif//__INGREDIENT_CONTROLLER