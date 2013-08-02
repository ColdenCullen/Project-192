#include "TaskManager.h"
#include <iostream>

using namespace std;
using namespace Graphos::Core;

void Graphos::Core::TaskManager::Initialize( void )
{	// If no thread count is specified, use system number
	int systemThreadCount = thread::hardware_concurrency();

	// If hardware_concurrency is 0, use 1 worker thread
	Initialize( systemThreadCount > 2 ? systemThreadCount - 2 : 1 );
}

void TaskManager::Initialize( int initThreadCount  )
{
	// Assign thread count
	numThreads = initThreadCount;

	running = true;

	monitorThread = new thread( &TaskManager::Monitor, this );
}

void TaskManager::AddTask( Task task )
{
	monitorMutex.lock();
	if( workers.size() >= numThreads )
		tasksWaiting.push_back( task );
	else
		workers.push_back( std::thread( task ) );
	monitorMutex.unlock();
}

void TaskManager::WaitForCompletion( void )
{
	while( workers.size() );
}

void TaskManager::Monitor( void )
{
	// Get this id, and make sure that it matches the proper thread
	auto thisId = this_thread::get_id();
	if( thisId != monitorThread->get_id() )
		throw exception( "DO NOT CALL THIS FUNCTION." );

	int count = 0;
	while( running || workers.size() )
	{
		//cout << "Monitor: " << count++ << endl;
		if( !workers.size() && !tasksWaiting.size() )
			continue;

		monitorMutex.lock();
		for( int ii = 0; ii < workers.size(); ++ii )
		{
			auto& task = workers.at( ii );
			if( task.joinable() )
			{
				task.join();
				workers.erase( workers.begin() + ii );
			}
		}

		while( workers.size() < numThreads && tasksWaiting.size() > 0 )
		{
			auto& task = tasksWaiting.front();
			tasksWaiting.pop_front();
			workers.push_back( thread( task ) );
		}
		monitorMutex.unlock();
	}
}

void TaskManager::Shutdown( void )
{
	WaitForCompletion();

	running = false;
	if( monitorThread->joinable() )
		monitorThread->join();

	delete monitorThread;
}
