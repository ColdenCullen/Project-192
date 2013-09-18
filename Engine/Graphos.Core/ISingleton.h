#ifndef __ISINGLETON
#define __ISINGLETON

#include "IController.h"
#include <type_traits>

namespace Graphos
{
	namespace Core
	{
		//, typename = std::enable_if<std::is_base_of<IController, TController>::value>::type
		template<typename TController>
		class ISingleton
		{
		public:
			static TController&	Get( void )
			{
				static TController instance;
				return instance;
			}
		};
	}
}

#endif//_ISINGLETON