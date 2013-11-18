#include "ThreadManager.h"
#include <iostream>

using namespace std;
using namespace Graphos::Utility;

mutex ThreadManager::monitorMutex;
bool* ThreadManager::workerAvailablibility;
thread* ThreadManager::workers;
deque<ThreadManager::Task> ThreadManager::tasksWaiting;
deque<ThreadManager::Task> ThreadManager::invokeQueue;
int ThreadManager::runningThreads;
int ThreadManager::numThreads;
thread::id ThreadManager::main_thread;

void ThreadManager::Initialize( void )
{	// If no thread count is specified, use system number
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
	workers = new thread[ numThreads ];
	workerAvailablibility = new bool[ numThreads ];
}

void ThreadManager::AddTask( Task task )
{
	monitorMutex.lock();
	if( runningThreads >= numThreads )
	{
		tasksWaiting.push_back( task );
	}
	else
	{
		for( int ii = 0; ii < numThreads; ++ii )
		{
			if( workerAvailablibility[ ii ] )
			{
				workerAvailablibility[ ii ] = false;
				workers[ ii ] = thread( &ThreadManager::ExecuteTask, task, ii );
				++runningThreads;
				break;
			}
		}
	}
	monitorMutex.unlock();
}

void ThreadManager::Invoke( Task task )
{
	invokeQueue.push_back( task );
}

void ThreadManager::ExecuteTask( Task task, int index )
{
	// Execute task
	task();

	// Detach this thread and let it finish
	if( workers[ index ].joinable() )
		workers[ index ].detach();
	else
	{
		//_CrtDbgBreak();
		workers[ index ].join();
	}

	monitorMutex.lock();
	if( !tasksWaiting.empty() )
	{	// If there are tasks waiting, start one
		auto newTask = tasksWaiting.front();
		tasksWaiting.pop_front();

		workers[ index ] = thread( &ThreadManager::ExecuteTask, newTask, index );
	}
	else
	{	// Else, mark thread as done
		workerAvailablibility[ index ] = true;
		--runningThreads;

		workers[ index ] = thread();// = thread();
	}
	monitorMutex.unlock();
}

void ThreadManager::WaitForCompletion( void )
{
	for( auto task : invokeQueue )
	{
		task();
	}

	while( runningThreads > 0  ) ;
}

void ThreadManager::Shutdown( void )
{
	WaitForCompletion();

	delete[] workers;
	delete[] workerAvailablibility;
}
