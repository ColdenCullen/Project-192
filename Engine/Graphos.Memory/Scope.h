#ifndef __SCOPE
#define __SCOPE

#include <stack>
#include <vector>

namespace Graphos
{
	namespace Memory
	{
		// Forward declaration
		template<typename T>
		struct Handle;

		class Scope
		{
		public:
			// Gets current scope on top
			static Scope*		GetTopScope( void ) { return current.top(); }

			Scope( void );
			~Scope( void );

			// Add handle to current scope
			template<typename T>
			void				AddHandle( Handle<T>* handle )
			{
				handles.push_back( handle );
			}
			// Remove handle from vector
			template<typename T>
			void				RemoveHandle( Handle<T>* handle )
			{
				auto itr = handles.find( handle );

				if( itr != end( handles ) )
					delete_s( itr->second );
			}

		private:
			// Current top scope stack
			static
			std::stack<Scope*>	current;
			// Handles in current scope
			std::vector<void*>	handles;
		};
	}
}

#endif//__SCOPE
