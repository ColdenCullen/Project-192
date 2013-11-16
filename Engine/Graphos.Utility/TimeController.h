#ifndef __TIME
#define __TIME

#include <chrono>

using namespace std::chrono;

namespace Graphos
{
	namespace Utility
	{
		class Time
		{
		public:
			static void			Initialize( void );
			static void			Update( void );
			static const gFloat	GetDeltaTime( void ) { return static_cast<gFloat>( deltaTime.count() ) / std::nano::den; }
			static const gFloat	GetTotalTime( void ) { return static_cast<gFloat>( totalTime.count() ) / std::nano::den; }

		private:
			static std::chrono::high_resolution_clock::time_point
								cur;
			static std::chrono::high_resolution_clock::time_point
								prev;
			static std::chrono::nanoseconds
								deltaTime;
			static std::chrono::nanoseconds
								totalTime;
			static gUInt		frameCount;

			static std::chrono::nanoseconds
								secondTime;

								Time( void );
								Time( const Time& );
			void				operator=( const Time& );
		};
	}
}

#endif//__TIME