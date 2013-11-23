#ifndef __TASK_MANAGER
#define __TASK_MANAGER

#include <thread>
#include <deque>
#include <array>
#include <mutex>

namespace Graphos
{
	namespace Utility
	{
		class TaskManager
		{
		public:
			typedef	std::function<void(void)> Task;

			static const gInt	DefaultThreadCount = -1;

			static void		Initialize( void );
			static void		Initialize( int initThreadCount );
			static void		Shutdown( void );

			static const bool OnMainThread( void )			{ return std::this_thread::get_id() == main_thread; }
			static const gInt& GetThreadCount( void )		{ return numThreads; }
			static const gInt& GetActiveThreadCount( void )	{ return runningThreads; }

			static void		AddTask( Task task );
			static void		Invoke( Task task );
			static void		WaitForCompletion( void );
			static void		ExecuteTask( Task task, int index );

		private:
			static gInt		numThreads;
			static gInt		runningThreads;
			static std::deque<Task>	tasksWaiting;

			static std::deque<Task> invokeQueue;
			static std::thread*	workers;
			static gBool*	workerAvailablibility;

			static std::mutex monitorMutex;
			static std::thread::id main_thread;

							TaskManager( void ) { }
							TaskManager( const TaskManager& );
			TaskManager&	operator=( const TaskManager& );
		};
	}
}

#endif//__TASK_MANAGER
