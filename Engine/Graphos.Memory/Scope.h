#ifndef __SCOPE
#define __SCOPE

#include <stack>
#include <map>

#include "Handle.h"

namespace Graphos
{
	namespace Memory
	{
		class Scope
		{
		public:
			// Gets current scope on top
			static Scope*		GetTopScope( void ) { return current.top(); }

								Scope( void );
								~Scope( void );

			// Add handle to current scope
			template<typename T>
			Handle<T>			AddHandle( T* newValue )
			{
				auto handle = new Handle<T>( newValue, this, currentId );
				handles[ currentId++ ] = handle;
				return *handle;
			}
			// Remove handle from vector
			template<typename T>
			void				RemoveHandle( Handle<T>* handle )
			{
				delete_s( handle->ptr );

				// Remove handle from map
				auto at = handles.find( handle->id );
				if( at != handles.end() )
					handles.erase( at );
			}

		private:
			// Current top scope stack
			static
			std::stack<Scope*>	current;
			// Handles in current scope
			std::map<unsigned int, IHandle*>
								handles;
			// Current id
			unsigned int		currentId;

			template<typename H>
			friend struct		Handle;
		};
	}
}

#endif//__SCOPE
