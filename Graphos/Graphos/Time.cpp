#include "Time.h"

#ifdef _DEBUG
#include <iostream>
using namespace std;
#endif//_DEBUG

using namespace std::chrono;
using namespace Graphos::Core;

void Time::Update( void )
{
	prev = cur;
	cur = high_resolution_clock::now();

	deltaTime = duration_cast<nanoseconds>( cur - prev );
	totalTime += deltaTime;

	// Update framerate
#ifdef _DEBUG
	secondTime += deltaTime;
	++frameCount;

	if( secondTime.count() >= nano::den )
	{
		cout << frameCount << endl;
		secondTime = nanoseconds::zero();
		frameCount = 0;
	}
#endif//_DEBUG
}

#ifdef _DEBUG
Time::Time( void ) : cur( high_resolution_clock::now() ), prev( high_resolution_clock::now() ), totalTime( 0 ), frameCount( 0 ), secondTime( 0 ) { }
#else
Time::Time( void ) : cur( high_resolution_clock::now() ), prev( high_resolution_clock::now() ), totalTime( 0 ) { }
#endif