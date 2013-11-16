#include "WindowController.h"
#include "Win32Controller.h"

using namespace Graphos::Graphics;

WindowController* WindowController::Get()
{
#if defined( _WIN32 )
	static Win32Controller wInstance;
	return &wInstance;
#elif defined( __APPLE__ )
	static OSXController osxInstance;
	return &osxInstance;
#else
	return nullptr;
#endif//_WIN32||__APPLE__
}
