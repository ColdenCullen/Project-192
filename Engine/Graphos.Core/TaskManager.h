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
			const int&			GetActiveThreadCount( void )	{ return workers.size(); }

			void				AddTask( Task task );
			void				WaitForCompletion( void );

			// DO NOT CALL!! For internal use only
			void				Monitor( void );

		private:
			int					numThreads;
			bool				running;
			std::deque<Task>	tasksWaiting;
			std::deque<std::thread>
				workers;
			std::thread*		monitorThread;
			std::mutex			monitorMutex;

			TaskManager( void ) { }
			TaskManager( const TaskManager& );
			TaskManager&		operator=( const TaskManager& );
		};
	}
}

#endif//__TASK_MANAGER
