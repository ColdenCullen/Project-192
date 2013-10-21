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
void Graphos::Core::Time::Initialize( void )
{
	cur = high_resolution_clock::now();
	prev = high_resolution_clock::now();
	totalTime = nanoseconds::zero();
	frameCount = 0;
	secondTime = nanoseconds::zero();
}

// Statics
unsigned int Time::frameCount;
nanoseconds Time::secondTime;
nanoseconds Time::totalTime;
nanoseconds Time::deltaTime;
high_resolution_clock::time_point Time::prev;
high_resolution_clock::time_point Time::cur;
