#include "Thread.h"

using namespace Graphos::Utility;

void Thread::Invoke( Task task )
{
	queuedTasks.push_back( task );
}
