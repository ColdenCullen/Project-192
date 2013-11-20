#include "GraphosThread.h"
#include "OutputController.h"
#include "ThreadController.h"

using namespace std;
using namespace Graphos::Utility;

Thread::Thread( void )
{
	running = true;
	thisThread = thread( &Thread::Execute, this );
}

void Thread::Invoke( Thread::Task task, gBool sync )
{
	if( this_thread::get_id() == thisThread.get_id() )
	{
		task();
	}
	else
	{
		if( sync )
		{
			bool isDone = false;

			queuedTasks.push_back( [&]()
			{
				task();
				isDone = true;
			} );

			while( !isDone );
		}
		else
		{
			thisMutex.lock();
			queuedTasks.push_back( task );
			thisMutex.unlock();
		}
	}
}

void Thread::Execute( void )
{
	if( this_thread::get_id() != thisThread.get_id() )
		OutputController::PrintMessage( OutputType::Error, "Thread::Execute call from invalid thread." );

	while( running || queuedTasks.size() )
	{
		// Wait for tasks
		if( queuedTasks.size() )
		{
			isBusy = true;

			thisMutex.lock();
			auto task = queuedTasks.front();
			queuedTasks.pop_front();
			thisMutex.unlock();

			task();
		}
		else
		{
			isBusy = false;
			this_thread::yield();
		}
	}
}

void Thread::Stop( void )
{
	running = false;
	queuedTasks.clear();
	WaitFor();
}
