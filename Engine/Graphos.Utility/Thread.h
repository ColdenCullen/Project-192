#ifndef __THREAD
#define __THREAD

#include <thread>
#include <deque>

namespace Graphos
{
	namespace Utility
	{
		class Thread
		{
		public:
			typedef	std::function<void(void)> Task;

			void				Invoke( Task task );

		private:
			std::thread::id		id;
			std::thread			thread;
			std::deque<Task>	queuedTasks;
		};
	}
}

#endif//__THREAD