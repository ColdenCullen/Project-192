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

			static TaskManager&	Get( void )
			{
				static TaskManager instance;
				return instance;
			}

			virtual void		Initialize( void );
			virtual void		Initialize( int initThreadCount  );
			virtual void		Shutdown( void );

			const int&			GetThreadCount( void )			{ return numThreads; }
			const int&			GetActiveThreadCount( void )	{ return runningThreads; }

			void				AddTask( Task task );
			void				WaitForCompletion( void );

			void				ExecuteTask( Task task, int index );

		private:
			int					numThreads;
			int					runningThreads;
			std::deque<Task>	tasksWaiting;
			std::thread*		workers;
			bool*				workerAvailablibility;
			std::mutex			monitorMutex;

			TaskManager( void ) { }
			TaskManager( const TaskManager& );
			TaskManager&		operator=( const TaskManager& );
		};
	}
}

#endif//__TASK_MANAGER
