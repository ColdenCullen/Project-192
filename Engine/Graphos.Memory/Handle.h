#ifndef __HANDLE
#define __HANDLE

#include "Scope.h"

namespace Graphos
{
	namespace Memory
	{
		template<typename T>
		struct Handle
		{
		public:
			// Creates new handle with pointer to memory
			Handle( void* ptr, Scope* owner )
				: ptr( static_cast<void*>( ptr ) ), owner( owner ) { }

			// Public-facing delete method, removes handle from scope
			void Delete( void )
			{
				delete_s( ptr );
			}
			// Deletes memory and removes handle
			~Handle( void )
			{
				Delete();
			}

			T& operator->( void )
			{
				return *ptr;
			}

			T& operator*( void )
			{
				return *ptr;
			}

		private:
			// Pointer to memory
			T* ptr;
			// Scope that owns this handle
			Scope* owner;

			friend class Scope;
		};
	}
}

#endif//__HANDLE
