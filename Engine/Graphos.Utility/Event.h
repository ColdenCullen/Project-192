#ifndef __EVENT
#define __EVENT

#include <vector>
#include <functional>

namespace Graphos
{
	namespace Utility
	{
		template<typename TArgs>
		struct Event
		{
		public:
			typedef std::function<void(TArgs)> Delegate;
		
			void AddFunction( Delegate func )
			{
				functions.push_back( func );
			}

			void Call( TArgs arguments ) const
			{
				for( auto func : functions )
					func( arguments NULL );
			}

			void operator+=( Delegate func )
			{
				AddFunction( func );
			}

			void operator()( TArgs arguments ) const
			{
				Call( arguments );
			}

		private:
			std::vector<Delegate> functions;
		};
	}
}

#endif//__EVENT
