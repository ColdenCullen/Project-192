#ifndef __GAME_OBJECT_COLLECTION
#define __GAME_OBJECT_COLLECTION

#include "GameObject.h"
#include "IShader.h"

#include <string>
#include <unordered_map>

namespace Graphos
{
	namespace Core
	{
		class GameObjectCollection
		{
		public:
			// Load object from resources folder
			void				LoadObjects( std::string assetPath = "" );

			// Add object
			unsigned int		CreateObject( std::string name, Graphics::IShader* shader );

			// Access objects
			GameObject*			GetObjectById( unsigned int id );
			GameObject*			GetObjectByName( std::string name );

			// Remove Objects
			void				RemoveObjectById( unsigned int id );
			void				RemoveObjectByName( std::string name );
			void				ClearObjects( void );

			// Per-object operations
			void				CallFunction( void (GameObject::*func)( void ) );

		private:
			std::unordered_map<unsigned int, GameObject*>
								objectList;
			std::unordered_map<std::string, unsigned int>
								nameMap;

			unsigned int		currentId;
		};
	}
}

#endif//__GAME_OBJECT_COLLECTION