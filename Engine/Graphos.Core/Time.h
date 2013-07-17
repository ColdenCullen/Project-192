#ifndef __TIME
#define __TIME

#include <ratio>
#include <chrono>

namespace Graphos
{
	namespace Core
	{
		class Time
		{
		public:
			static Time&		Get( void )
			{
				static Time instance;
				return instance;
			}

			void				Update( void );
			const float			GetDeltaTime( void ) const { return static_cast<float>( deltaTime.count() ) / std::nano::den; }
			const float			TotalTime( void ) const { return static_cast<float>( totalTime.count() ) / std::nano::den; }

		private:
			std::chrono::high_resolution_clock::time_point
								cur;
			std::chrono::high_resolution_clock::time_point
								prev;
			std::chrono::nanoseconds
								deltaTime;
			std::chrono::nanoseconds
								totalTime;

#ifdef _DEBUG
			unsigned int		frameCount;

			std::chrono::nanoseconds
								secondTime;

								Time( void );
#else
								Time( void );
#endif//_DEBUG
								Time( const Time& );
			void				operator=( const Time& );
		};
	}
}

#endif//__TIME