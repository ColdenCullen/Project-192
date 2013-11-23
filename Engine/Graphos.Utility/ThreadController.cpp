#include <iostream>

#include "ThreadController.h"

using namespace std;
using namespace Graphos::Utility;

thread::id ThreadController::main_thread;
mutex ThreadController::globalMutex;
gUInt ThreadController::numThreads;
unordered_map<string, Thread*> ThreadController::reservedThreads;

void ThreadController::Initialize( void )
{
	// If no thread count is specified, use system number
	gUInt systemThreadCount = thread::hardware_concurrency();

	// If hardware_concurrency is 0, use 1 worker thread
	Initialize( systemThreadCount > 1 ? systemThreadCount - 1 : 1 );
}

void ThreadController::Initialize( int initThreadCount  )
{
	// Assign thread count
	numThreads = initThreadCount;

	main_thread = this_thread::get_id();
}

Thread* ThreadController::ReserveThread( std::string name )
{
	Thread* thr = new Thread();

	if( name.size() )
		reservedThreads[ name ] = thr;

	return thr;
}

const gInt ThreadController::GetBusyThreadCount( void )
{
	gInt busyCount = 0;
	for( auto thread : reservedThreads )
		busyCount += thread.second->IsBusy();
	return busyCount;
}

void ThreadController::WaitForCompletion( void )
{
	while( GetBusyThreadCount() > 0  ) ;
}

void ThreadController::Shutdown( void )
{
	WaitForCompletion();

	GlobalLock();
	for( auto thread : reservedThreads )
	{
		thread.second->Stop();
		delete thread.second;
	}
	reservedThreads.clear();
	GlobalUnlock();
}
