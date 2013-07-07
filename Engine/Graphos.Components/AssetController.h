#ifndef __ASSET_CONTROLLER
#define __ASSET_CONTROLLER

#include <unordered_map>
#include <string>

#include "IComponent.h"
#include "IController.h"

namespace Graphos
{
	namespace Core
	{
		class AssetController : public IController
		{
		public:
			static
			AssetController&	Get( void )
			{
				static AssetController instance;
				return instance;
			}

			virtual void		Initialize( void ) override;
			virtual void		Shutdown( void ) override;

			// Returns content of the given type with the given name
			template<class T>
			typename std::enable_if<std::is_base_of<IComponent, T>::value, T*>::type
								GetContent( std::string name )
			{
				return dynamic_cast<T*>( ingredientShelf[ name ] );
			}

		private:
								AssetController( void ) { }
								AssetController( const AssetController& other );
			AssetController&	operator=( const AssetController& other );

			std::unordered_map<std::string, IComponent*>
								ingredientShelf;
		};
	}
}

#endif//__ASSET_CONTROLLER