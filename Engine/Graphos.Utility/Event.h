#ifndef __EVENT
#define __EVENT

#include <vector>
#include <functional>

namespace Graphos
{
	namespace Utility
	{
		template<typename TReturn, typename TArgs>
		struct Event
		{
		public:
			typedef std::function<TReturn(TArgs)> Delegate;
		
			virtual void AddFunction( Delegate func )
			{
				functions.push_back( func );
			}

			virtual void Call( TArgs arguments ) const
			{
				for( auto func : functions )
					func( arguments );
			}

			virtual void operator+=( Delegate func )
			{
				AddFunction( func );
			}

			virtual void operator()( TArgs arguments ) const
			{
				Call( arguments );
			}

		private:
			std::vector<Delegate> functions;
		};

		template<typename TReturn>
		struct Event<TReturn, void>
		{
		public:
			typedef std::function<TReturn(void)> Delegate;

			virtual void AddFunction( Delegate func )
			{
				functions.push_back( func );
			}

			virtual void Call( void ) const
			{
				for( auto func : functions )
					func();
			}

			virtual void operator+=( Delegate func )
			{
				AddFunction( func );
			}

			virtual void operator()( void ) const
			{
				Call();
			}

		private:
			std::vector<Delegate> functions;
		};
	}
}

#endif//__EVENT
