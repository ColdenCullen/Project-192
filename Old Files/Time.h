#ifndef __TIME
#define __TIME

#include <ctime>

namespace Graphos
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
		const float			DeltaTime( void ) const { return deltaTime; }
		const float			TotalTime( void ) const { return totalTime; }

	private:
		long				cur;
		long				prev;
		float				deltaTime;
		float				totalTime;

#if defined( _DEBUG )
		unsigned int		frameCount;
		float				secondTime;

							Time( void ) : cur( clock() ), prev( clock() ), totalTime( 0.0f ), frameCount( 0 ), secondTime( 0.0f ) { }
#else
							Time( void ) : cur( clock() ), prev( clock() ), totalTime( 0.0f ) { }
#endif//_DEBUG
							Time( const Time& );
		void				operator=( const Time& );
	};
}

#endif//__TIME