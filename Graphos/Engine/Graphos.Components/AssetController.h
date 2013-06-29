#ifndef __ASSET_CONTROLLER
#define __ASSET_CONTROLLER

#include <unordered_map>
#include <string>

#include "Component.h"

namespace Graphos
{
	namespace Core
	{
		class AssetController
		{
		public:
			static
			AssetController&	Get( void )
			{
				static AssetController instance;
				return instance;
			}

			bool				Initialize( void );
			void				Shutdown( void );

			// Returns content of the given type with the given name
			template<class T>
			typename std::enable_if<std::is_base_of<Component, T>::value, T*>::type
								GetContent( std::string name )
			{
				return dynamic_cast<T*>( ingredientShelf[ name ] );
			}

		private:
								AssetController( void ) { }
								AssetController( const AssetController& other );
			AssetController&	operator=( const AssetController& other );

			std::unordered_map<std::string, Component*>
								ingredientShelf;
		};
	}
}

#endif//__ASSET_CONTROLLER