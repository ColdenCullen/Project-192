#ifndef __GAME_OBJECT_COLLECTION
#define __GAME_OBJECT_COLLECTION

#include <string>
#include <unordered_map>

#include "OutputController.h"
#include "GameObject.h"
#include "IShader.h"

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
			GameObject*			GetObjectById( gUInt id );
			GameObject*			GetObjectByName( std::string name );

			// Remove Objects
			void				RemoveObjectById( gUInt id );
			void				RemoveObjectByName( std::string name );
			void				ClearObjects( void );

			// Per-object operations
			void				CallFunction( void (GameObject::*func)( void ) );

			void Update( void ) { CallFunction( &GameObject::Update ); }
			void Draw( void ) { CallFunction( &GameObject::Draw ); }

		private:
			std::unordered_map<gUInt, GameObject*>
								objectList;
			std::unordered_map<std::string, gUInt>
								nameMap;

			gUInt				currentId;
		};
	}
}

#endif//__GAME_OBJECT_COLLECTION