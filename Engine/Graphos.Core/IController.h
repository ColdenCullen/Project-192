#ifndef __ICONTROLLER
#define __ICONTROLLER

namespace Graphos
{
	namespace Core
	{
		class IController
		{
		public:
			virtual void		Initialize( void ) { }
			virtual void		Shutdown( void ) { }
		};
	}
}

#endif//__ICONTROLLER