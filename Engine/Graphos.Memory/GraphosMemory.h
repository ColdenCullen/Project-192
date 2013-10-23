#ifndef __GRAPHOS_MEMORY
#define __GRAPHOS_MEMORY

#include "Scope.h"
#include "Handle.h"

template<typename T>
Graphos::Memory::Handle<T> gnew( void )
{
	return Graphos::Memory::Scope::GetTopScope()->AddHandle( new T );
}

#endif//__GRAPHOS_MEMORY
