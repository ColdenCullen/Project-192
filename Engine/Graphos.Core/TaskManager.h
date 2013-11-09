#ifndef __TASK_MANAGER
#define __TASK_MANAGER

#include <thread>
#include <deque>
#include <mutex>

namespace Graphos
{
	namespace Core
	{
		class TaskManager
		{
		public:
			typedef	std::function<void(void)> Task;

			static const int	DefaultThreadCount = -1;

			static void		Initialize( void );
			static void		Initialize( int initThreadCount  );
			static void		Shutdown( void );

			static const int& GetThreadCount( void )		{ return numThreads; }
			static const int& GetActiveThreadCount( void )	{ return runningThreads; }

			static void		AddTask( Task task );
			static void		WaitForCompletion( void );
			static void		ExecuteTask( Task task, int index );

		private:
			static int		numThreads;
			static int		runningThreads;
			static std::deque<Task>	tasksWaiting;
			static std::thread*	workers;
			static bool*	workerAvailablibility;
			static std::mutex monitorMutex;

							TaskManager( void ) { }
							TaskManager( const TaskManager& );
			TaskManager&	operator=( const TaskManager& );
		};
	}
}

#endif//__TASK_MANAGER
