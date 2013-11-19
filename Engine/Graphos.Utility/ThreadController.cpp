#include <iostream>

#include "ThreadController.h"

using namespace std;
using namespace Graphos::Utility;

thread::id ThreadController::main_thread;
mutex ThreadController::globalMutex;
Thread** ThreadController::workers;
deque<Thread::Task> ThreadController::tasksWaiting;
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

	// Create arrays of workers
	workers = new Thread*[ numThreads ];
	for( gUInt ii = 0; ii < numThreads; ++ii )
		workers[ ii ] = nullptr;
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
	for( gUInt ii = 0; ii < numThreads; ++ii )
		busyCount += workers[ ii ] && workers[ ii ]->IsBusy();
	for( auto thread : reservedThreads )
		busyCount += thread.second->IsBusy();
	return busyCount;
}

void ThreadController::AddTask( Thread::Task task )
{
	if( GetBusyThreadCount() >= numThreads )
	{
		tasksWaiting.push_back( task );
	}
	else
	{
		for( int ii = 0; ii < numThreads; ++ii )
		{
			if( !workers[ ii ]->IsBusy() )
			{
				workers[ ii ]->Invoke( task );
				break;
			}
		}
	}
}

void ThreadController::WaitForCompletion( void )
{
	while( GetBusyThreadCount() > 0  ) ;
}

void ThreadController::Shutdown( void )
{
	WaitForCompletion();

	GlobalLock();
	for( gUInt ii = 0; ii < numThreads; ++ii )
	{
		if( workers[ ii ] && workers[ ii ]->thisThread.joinable() )
			workers[ ii ]->thisThread.join();

		delete_s( workers[ ii ] );
	}
	delete[] workers;
	GlobalUnlock();
}
