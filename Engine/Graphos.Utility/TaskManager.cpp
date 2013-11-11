#include "TaskManager.h"
#include <iostream>

using namespace std;
using namespace Graphos::Utility;

mutex TaskManager::monitorMutex;
bool* TaskManager::workerAvailablibility;
thread* TaskManager::workers;
deque<TaskManager::Task> TaskManager::tasksWaiting;
deque<TaskManager::Task> TaskManager::invokeQueue;
int TaskManager::runningThreads;
int TaskManager::numThreads;
thread::id TaskManager::main_thread;

void TaskManager::Initialize( void )
{	// If no thread count is specified, use system number
	int systemThreadCount = thread::hardware_concurrency();

	// If hardware_concurrency is 0, use 1 worker thread
	Initialize( systemThreadCount > 1 ? systemThreadCount - 1 : 1 );
}

void TaskManager::Initialize( int initThreadCount  )
{
	// Assign thread count
	numThreads = initThreadCount;

	main_thread = this_thread::get_id();

	// Create arrays of workers
	workers = new thread[ numThreads ];
	workerAvailablibility = new bool[ numThreads ];
}

void TaskManager::AddTask( Task task )
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
				workers[ ii ] = thread( &TaskManager::ExecuteTask, task, ii );
				workerAvailablibility[ ii ] = false;
				++runningThreads;
				break;
			}
		}
	}
	monitorMutex.unlock();
}

void TaskManager::Invoke( Task task )
{
	invokeQueue.push_back( task );
}

void TaskManager::ExecuteTask( Task task, int index )
{
	// Execute task
	task();

	// Detach this thread and let it finish
	if( workers[ index ].joinable() )
		workers[ index ].detach();

	monitorMutex.lock();
	if( !tasksWaiting.empty() )
	{	// If there are tasks waiting, start one
		auto newTask = tasksWaiting.front();
		tasksWaiting.pop_front();

		workers[ index ] = thread( &TaskManager::ExecuteTask, newTask, index );
	}
	else
	{	// Else, mark thread as done
		--runningThreads;
		workerAvailablibility[ index ] = true;
	}
	monitorMutex.unlock();
}

void TaskManager::WaitForCompletion( void )
{
	for( auto task : invokeQueue )
	{
		task();
	}

	while( runningThreads > 0  ) ;
}

void TaskManager::Shutdown( void )
{
	WaitForCompletion();

	delete[] workers;
	delete[] workerAvailablibility;
}
