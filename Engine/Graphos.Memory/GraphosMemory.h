#ifndef __GRAPHOS_MEMORY
#define __GRAPHOS_MEMORY

#include "Scope.h"
#include "Handle.h"

template<typename T>
Graphos::Memory::Handle<T> gnew( void )
{
	using namespace Graphos::Memory;

	auto top = Scope::GetTopScope();
	auto hndl = new Handle<T>( new T, top );
	top->AddHandle( hndl );
	return *hndl;
}

#endif//__GRAPHOS_MEMORY
