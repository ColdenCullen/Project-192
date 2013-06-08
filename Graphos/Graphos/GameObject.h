#ifndef __GAME_OBJECT
#define __GAME_OBJECT

// Includes
#include <string>
#include <unordered_map>
#include <type_traits>

#include "Component.h"
#include "Transform.h"
#include "ShaderController.h"
#include "Shader.h"

using namespace Graphos::Graphics;

namespace Graphos
{
	namespace Core
	{
		class GameObject
		{
#pragma region Static Stuff
		public:
			// Type for use with object lists
			typedef std::unordered_map<unsigned int, GameObject> GOMap;

			// Access objects
			static GameObject*	GetGameObject( std::string name );
			static GameObject*	GetGameObject( unsigned int id );
			static GOMap&		GetObjectsList( void )
			{
				return objectList;
			}

			// Add object
			static unsigned int	CreateObject( std::string name, Shader* shader );
			static unsigned int CreateObject( std::string name, GameObject newObj );

			// Remove objects
			static void			ClearObjects( void )
			{
				objectList.clear();
				nameMap.clear();
			}

		private:
			static GOMap		objectList;
			static std::unordered_map<std::string, unsigned int>
								nameMap;

			static unsigned int	currentId;
#pragma endregion

#pragma region Not Static Stuff
		public:
			Transform			transform;

			// Constructors
			GameObject( void ) : shader( nullptr ) { }
			GameObject( Shader* shader ) : shader( shader ) { }

			// Shutdown memory
			void				Shutdown( void );

			// Game logic
			bool				Update( float deltaTime );
			void				Draw( void );
			virtual void		OnCollision( GameObject* other ) { }

			// Getters and setters
			Shader&				GetShader( void ) const { return *shader; }
			void				SetShader( std::string newName ) { shader = &( ShaderController::Get().GetShader( newName ) ); }

			// Add ingredient of type T
			template<class T>
			typename std::enable_if<std::is_base_of<Component, T>::value, void>::type
								AddComponent( T* newIngredient )
			{
				componentList[ typeid(T).hash_code() ] = newIngredient;
			}

			// Get ingredient of type T
			template<class T>
			typename std::enable_if<std::is_base_of<Component, T>::value, T*>::type
								GetComponent( void )
			{
				auto itr = componentList.find( typeid(T).hash_code() );

				if( itr != end( componentList ) )
					return static_cast<T*>( itr->second );
				else
					return nullptr;
			}

		private:
			std::unordered_map<size_t, Component*>
								componentList;

			Shader*				shader;
#pragma endregion
		};
	}
}

#endif//__GAME_OBJECT