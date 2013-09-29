#include "TimeController.h"
#include "OutputController.h"
#include <ratio>

using namespace std;
using namespace std::chrono;
using namespace Graphos::Core;

void Time::Update( void )
{
	prev = cur;
	cur = high_resolution_clock::now();

	deltaTime = duration_cast<nanoseconds>( cur - prev );
	totalTime += deltaTime;

	// Update framerate
	secondTime += deltaTime;
	++frameCount;

	if( secondTime.count() >= nano::den )
	{
		ISingleton<OutputController>::Get().PrintValue( OutputType::OT_INFO, "Framerate", (signed int)frameCount );
		secondTime = nanoseconds::zero();
		frameCount = 0;
	}
}

Time::Time( void ) : cur( high_resolution_clock::now() ), prev( high_resolution_clock::now() ), totalTime( 0 ), frameCount( 0 ), secondTime( 0 ) { }
