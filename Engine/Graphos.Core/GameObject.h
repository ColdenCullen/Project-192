#ifndef __GAME_OBJECT
#define __GAME_OBJECT

// Includes
#include <string>
#include <unordered_map>
#include <type_traits>

#include "JsonObject.h"
#include "IComponent.h"
#include "Transform.h"
#include "ShaderController.h"

namespace Graphos
{
	namespace Core
	{
		class GameObject 
		{
		public:
			Math::Transform*	transform;

			// Constructors
			GameObject( void ) : shader( nullptr ), transform( new Math::Transform ) { }
			GameObject( Graphics::IShader* shader ) : shader( shader ), transform( new Math::Transform ) { }

			// Factory for creating game objects from json
			static GameObject*	CreateFromJson( Utility::JsonObject object );

			// Shutdown memory
			void				Shutdown( void );

			// Game logic
			void				Update( void );
			void				Draw( void );
			virtual void		OnCollision( GameObject* other ) { }

			// Getters and setters
			Graphics::IShader*	GetShader( void ) const { return shader; }
			void				SetShader( std::string newName ) { shader = Graphics::ShaderController::GetShader( newName ); }

			// Add ingredient of type T
			template<class T>
			typename std::enable_if<std::is_base_of<IComponent, T>::value, void>::type
								AddComponent( T* newIngredient )
			{
				componentList[ typeid(T).hash_code() ] = newIngredient;
			}

			// Get ingredient of type T
			template<class T>
			typename std::enable_if<std::is_base_of<IComponent, T>::value, T*>::type
								GetComponent( void )
			{
				auto itr = componentList.find( typeid(T).hash_code() );

				if( itr != end( componentList ) )
					return static_cast<T*>( itr->second );
				else
					return nullptr;
			}

		private:
			std::unordered_map<gSize, IComponent*>
								componentList;

			Graphics::IShader*	shader;
		};
	}
}

#endif//__GAME_OBJECT