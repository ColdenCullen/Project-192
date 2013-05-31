#include "TestGame.h"
//#define _CHECK_LEAKS

#pragma region Suplimental Stuff
#if defined( _WIN32 )

 // Turn off console
 #ifndef _DEBUG
  #pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
 #endif//_DEBUG

 // Display memory leaks
 #if defined( _DEBUG ) && defined( _CHECK_LEAKS )
  #include <vld.h>
 #endif//_DEBUG && _CHECK_LEAKS

#elif defined( __APPLE__ )
 
#endif//_WIN32/__APPLE__
#pragma endregion

#if defined( _WIN32 )

int main()
{
	Graphos::TestGame test;
	test.Run();

	//system( "pause" );

	return 0;
}

#endif//_WIN32