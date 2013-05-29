#ifndef __GAME_OBJECT
#define __GAME_OBJECT
/*
// Includes
#include <string>
#include <unordered_map>
#include <type_traits>

#include "Ingredient.h"
#include "Transform.h"
#include "ShaderController.h"
#include "Shader.h"

using namespace std;
using namespace Graphos::Content;
using namespace Graphos::Graphics;

namespace Graphos
{
	namespace Core
	{
		class GameObject
		{
#pragma region Static Stuff
		public:
			// Access objects
			static GameObject*	GetGameObject( string name );
			static GameObject*	GetGameObject( unsigned int id );
			static unordered_map<unsigned int, GameObject>&
								GetObjectsList( void )
			{
				return objectList;
			}

			// Add object
			static unsigned int	CreateObject( string name, Shader* shader );
			static unsigned int CreateObject( string name, GameObject newObj );

			// Remove objects
			static void			ClearObjects( void )
			{
				objectList.clear();
				nameMap.clear();
			}

		private:
			static unordered_map<unsigned int, GameObject>
								objectList;
			static unordered_map<string, unsigned int>
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

			// Add ingredient of type T
			template<class T>
			typename enable_if<is_base_of<Ingredient, T>::value, void>::type
								AddIngredient( T* newIngredient )
			{
				recipe[ typeid(T).hash_code() ] = newIngredient;
			}

			// Get ingredient of type T
			template<class T>
			typename enable_if<is_base_of<Ingredient, T>::value, T*>::type
								GetIngredient( void )
			{
				auto itr = recipe.find( typeid(T).hash_code() );

				if( itr != end( recipe ) )
					return static_cast<T*>( itr->second );
				else
					return nullptr;
			}

			// Getters and setters
			Shader&				GetShader( void ) const { return *shader; }
			void				SetShader( string newName ) { shader = &( ShaderController::Get().GetShader( newName ) ); }

		private:
			unordered_map<size_t, Ingredient*>
								recipe;

			Shader*				shader;
#pragma endregion
		};
	}
}
*/
#endif//__GAME_OBJECT