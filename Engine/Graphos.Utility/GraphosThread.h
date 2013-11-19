#ifndef __THREAD
#define __THREAD

#include <thread>
#include <mutex>
#include <deque>

namespace Graphos
{
	namespace Utility
	{
		class Thread
		{
		public:
			typedef	std::function<void(void)> Task;

			const gBool			IsBusy( void ) { return isBusy; }
			
								Thread( void );

			const gBool			OnThread( void ) { return std::this_thread::get_id() == thisThread.get_id(); }
			const std::thread::id GetId( void ) { return thisThread.get_id(); }
			void				Invoke( Task task, gBool sync = false );

		private:
			std::thread			thisThread;
			std::mutex			thisMutex;
			std::deque<Task>	queuedTasks;
			gBool				running;
			gBool				isBusy;

			void				Execute( void );
		};
	}
}

#endif//__THREAD