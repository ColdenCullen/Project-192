#ifndef __TIME
#define __TIME

#include "IController.h"
#include "ISingleton.h"

#include <ratio>
#include <chrono>

namespace Graphos
{
	namespace Core
	{
		class Time : public IController
		{
		public:
			void				Update( void ) { } //;
			const float			GetDeltaTime( void ) const { return 1.0f;/*return static_cast<float>( deltaTime.count() ) / std::nano::den;*/ }
			const float			TotalTime( void ) const { return 1.0f;/*return static_cast<float>( totalTime.count() ) / std::nano::den;*/ }

		//private:
		//	std::chrono::high_resolution_clock::time_point
		//						cur;
		//	std::chrono::high_resolution_clock::time_point
		//						prev;
		//	std::chrono::nanoseconds
		//						deltaTime;
		//	std::chrono::nanoseconds
		//						totalTime;
		//	unsigned int		frameCount;

		//	std::chrono::nanoseconds
		//						secondTime;

								Time( void ) { }
								Time( const Time& );
			void				operator=( const Time& );

			friend class		ISingleton<Time>;
		};
	}
}

#endif//__TIME