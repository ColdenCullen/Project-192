#ifndef _CONTENTCONTROLLER_H_
#define _CONTENTCONTROLLER_H_

#include <unordered_map>
#include <string>

#include "Component.h"
#include "Mesh.h"
#include "Texture.h"

namespace Graphos
{
	namespace Core
	{
		class ContentController
		{
		public:
			bool				Initialize( void );
			void				Shutdown( void );

			// Returns content of the given type with the given name
			template<class T>
			typename std::enable_if<std::is_base_of<Component, T>::value, T*>::type
								GetContent( string name )
			{
				return dynamic_cast<T*>( components[ name ] );
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

			std::unordered_map<std::string, Component*>
								components;
		};
	}
}

#endif//_CONTENTCONTROLLER_H_