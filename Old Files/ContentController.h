#ifndef _CONTENTCONTROLLER_H_
#define _CONTENTCONTROLLER_H_

#include <algorithm>
#include <unordered_map>
#include <string>
//#include <FreeImage.h>

#include "Ingredient.h"
#include "Mesh.h"
#include "Texture.h"

using namespace std;

namespace Graphos
{
	namespace Content
	{
		class ContentController
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

			static
			ContentController&	Get( void )
			{
				static ContentController instance;
				return instance;
			}

		private:
								ContentController( void ) { }
								ContentController( const ContentController& other );
			ContentController&	operator=( const ContentController& other );

			unordered_map<string, Ingredient*>
								ingredientShelf;
		};
	}
}

#endif//_CONTENTCONTROLLER_H_