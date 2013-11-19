#include <iostream>

#include "ThreadManager.h"

using namespace std;
using namespace Graphos::Utility;

thread::id ThreadManager::main_thread;
Thread** ThreadManager::workers;
deque<Thread::Task> ThreadManager::tasksWaiting;
gUInt ThreadManager::numThreads;
unordered_map<string, Thread*> ThreadManager::reservedThreads;

void ThreadManager::Initialize( void )
{
	// If no thread count is specified, use system number
	gUInt systemThreadCount = thread::hardware_concurrency();

	// If hardware_concurrency is 0, use 1 worker thread
	Initialize( systemThreadCount > 1 ? systemThreadCount - 1 : 1 );
}

void ThreadManager::Initialize( int initThreadCount  )
{
	// Assign thread count
	numThreads = initThreadCount;

	main_thread = this_thread::get_id();

	// Create arrays of workers
	workers = new Thread*[ numThreads ];
}

Thread* ThreadManager::ReserveThread( std::string name )
{
	Thread* thr = new Thread();

	if( name.size() )
		reservedThreads[ name ] = thr;

	return thr;
}

const gInt ThreadManager::GetBusyThreadCount( void )
{
	gInt busyCount = 0;
	for( gUInt ii = 0; ii < numThreads; ++ii )
		busyCount += workers[ ii ]->IsBusy();
	return busyCount;
}

void ThreadManager::AddTask( Thread::Task task )
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

void ThreadManager::WaitForCompletion( void )
{
	while( GetBusyThreadCount() > 0  ) ;
}

void ThreadManager::Shutdown( void )
{
	WaitForCompletion();

	for( gUInt ii = 0; ii < numThreads; ++ii )
		delete_s( workers[ ii ] );
	delete[] workers;
}
