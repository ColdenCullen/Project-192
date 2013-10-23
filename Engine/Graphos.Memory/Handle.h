#ifndef __HANDLE
#define __HANDLE

namespace Graphos
{
	namespace Memory
	{
		class Scope;

		struct IHandle
		{
		public:
			virtual void Delete( void ) = 0;
		};

		template<typename T>
		struct Handle : public IHandle
		{
		private:
			typedef T* THandle;
			typedef T& TRef;

		public:
			// Creates new handle with pointer to memory
			Handle( THandle ptr, Scope* owner, unsigned int id )
				: ptr( ptr ), owner( owner ), id( id ) { }

			void Delete( void ) override
			{
				// Delete pointer
				delete_s( ptr );

				// Remove this from the current scope
				owner->RemoveHandle( this );
			}

			THandle operator->( void )
			{
				return ptr;
			}

			TRef operator*( void )
			{
				return *ptr;
			}

		private:
			// Pointer to memory
			THandle ptr;
			// Scope that owns this handle
			Scope* owner;
			// ID of handle
			unsigned int id;

			friend class Scope;
		};
	}
}

#endif//__HANDLE
