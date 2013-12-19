#ifndef __TIME
#define __TIME

#include <chrono>

using namespace std::chrono;

namespace Graphos
{
	namespace Utility
	{
		/**
		 * @class	Time
		 *
		 * @brief	Handles keeping track of time.
		 *
		 * @author	Colden Cullen
		 * @date	11/23/2013
		 */
		class Time
		{
		public:

			/**
			 * @fn	static void Time::Initialize( void );
			 *
			 * @brief	Initializes the time controller to keep track of time.
			 *
			 * @author	Colden Cullen
			 * @date	11/23/2013
			 */
			static void			Initialize( void );

			/**
			 * @fn	static void Time::Update( void );
			 *
			 * @brief	Updates the times.
			 *
			 * @author	Colden Cullen
			 * @date	11/23/2013
			 */
			static void			Update( void );

			/**
			 * @fn	static const gFloat Time::GetDeltaTime( void )
			 *
			 * @brief	Gets delta time.
			 *
			 * @author	Colden Cullen
			 * @date	11/23/2013
			 *
			 * @return	The delta time.
			 */
			static const gFloat	GetDeltaTime( void ) { return static_cast<gFloat>( deltaTime.count() ) / std::nano::den; }

			/**
			 * @fn	static const gFloat Time::GetTotalTime( void )
			 *
			 * @brief	Gets total run time.
			 *
			 * @author	Colden Cullen
			 * @date	11/23/2013
			 *
			 * @return	The total run time.
			 */
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