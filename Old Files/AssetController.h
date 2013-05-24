#ifndef _CONTENTCONTROLLER_H_
#define _CONTENTCONTROLLER_H_

#include <unordered_map>
#include <string>

#include "Ingredient.h"

using namespace std;

namespace Graphos
{
	namespace Content
	{
		class AssetController
		{
		public:
			bool				Initialize( void );
			void				Shutdown( void );

			// Returns content of the given type with the given name
			template<class T>
			typename enable_if<is_base_of<Ingredient, T>::value, T*>::type
								GetContent( string name )
			{
				return dynamic_cast<T*>( ingredientShelf[ name ] );
			}

			static AssetController&		Get( void )
			{
				static AssetController instance;
				return instance;
			}

		private:
								AssetController( void ) { }
								AssetController( const AssetController& other );
			AssetController&			operator=( const AssetController& other );

			unordered_map<string, Ingredient*>
								ingredientShelf;
		};
	}
}

#endif//_CONTENTCONTROLLER_H_