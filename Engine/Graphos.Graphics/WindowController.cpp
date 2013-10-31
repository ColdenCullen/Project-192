#include "WindowController.h"

using namespace Graphos::Graphics;

IPlatformWindowController* WindowController::Get()
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
