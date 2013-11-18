#ifndef __TASK_MANAGER
#define __TASK_MANAGER

#include <thread>
#include <deque>
#include <array>
#include <mutex>

#include "Thread.h"

namespace Graphos
{
	namespace Utility
	{
		class ThreadManager
		{
		public:

			static void		Initialize( void );
			static void		Initialize( int initThreadCount );
			static void		Shutdown( void );

			static const bool OnMainThread( void )			{ return std::this_thread::get_id() == main_thread; }
			static const gInt& GetThreadCount( void )		{ return numThreads; }
			static const gInt& GetActiveThreadCount( void )	{ return runningThreads; }

			static void		AddTask( Thread::Task task );
			static void		Invoke( Thread::Task task );
			static void		WaitForCompletion( void );
			static void		ExecuteTask( Thread::Task task, int index );

		private:
			static const gInt	DefaultThreadCount = -1;

			static gInt		numThreads;
			static gInt		runningThreads;
			static std::deque<Thread::Task>	tasksWaiting;

			static std::deque<Thread::Task> invokeQueue;
			static std::thread*	workers;
			static gBool*	workerAvailablibility;

			static std::mutex monitorMutex;
			static std::thread::id main_thread;

							ThreadManager( void ) { }
							ThreadManager( const ThreadManager& );
			ThreadManager&	operator=( const ThreadManager& );
		};
	}
}

#endif//__TASK_MANAGER
