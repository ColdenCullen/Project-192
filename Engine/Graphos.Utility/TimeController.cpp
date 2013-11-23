#include "TimeController.h"
#include "OutputController.h"
#include <ratio>

using namespace std;
using namespace std::chrono;
using namespace Graphos::Utility;

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
		OutputController::PrintValue( OutputType::Info, "Framerate", frameCount );
		secondTime = nanoseconds::zero();
		frameCount = 0;
	}
}
void Time::Initialize( void )
{
	cur = high_resolution_clock::now();
	prev = high_resolution_clock::now();
	totalTime = nanoseconds::zero();
	frameCount = 0;
	secondTime = nanoseconds::zero();
}

// Statics
gUInt Time::frameCount;
nanoseconds Time::secondTime;
nanoseconds Time::totalTime;
nanoseconds Time::deltaTime;
high_resolution_clock::time_point Time::prev;
high_resolution_clock::time_point Time::cur;
