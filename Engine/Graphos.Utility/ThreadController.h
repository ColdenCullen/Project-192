#ifndef __TASK_MANAGER
#define __TASK_MANAGER

#include <deque>
#include <mutex>
#include <string>
#include <unordered_map>

#include "GraphosThread.h"

namespace Graphos
{
	namespace Utility
	{
		class ThreadController
		{
		public:
			static void		Initialize( void );
			static void		Initialize( gInt initThreadCount );
			static void		Shutdown( void );

			static Thread*	ReserveThread( std::string name = "" );
			static Thread*	GetReservedThread( std::string name ) { return reservedThreads[ name ]; }

			static void		AddTask( Thread::Task task );
			static void		WaitForCompletion( void );

			static const gBool OnMainThread( void )			{ return std::this_thread::get_id() == main_thread; }
			static const gInt GetThreadCount( void )		{ return numThreads; }
			static const gInt GetBusyThreadCount( void );

			static void		GlobalLock( void )	{ globalMutex.lock(); }
			static void		GlobalUnlock( void ){ globalMutex.unlock(); }

		private:
			// Globals
			static const gInt DefaultThreadCount = -1;
			static std::thread::id main_thread;
			static std::mutex globalMutex;

			// For workers
			static gUInt	numThreads;
			static std::deque<Thread::Task>	tasksWaiting;
			static Thread**	workers;

			// For reserved threads
			static std::unordered_map<std::string, Thread*>
							reservedThreads;

							ThreadController( void ) { }
							ThreadController( const ThreadController& );
			ThreadController& operator=( const ThreadController& );
		};
	}
}

#endif//__TASK_MANAGER
