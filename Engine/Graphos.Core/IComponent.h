#ifndef __INGREDIENT
#define __INGREDIENT

namespace Graphos
{
	namespace Graphics
	{
		class Shader;
	}

	namespace Core
	{
		// Forward declaration
		class GameObject;

		class IComponent
		{
		public:
								IComponent( GameObject* owner = nullptr ) : owner( owner ) { }
			virtual				~IComponent( void ) { }

			virtual void		Update( void ) { };
			virtual void		Draw( Graphics::Shader* shader ) { };
			virtual void		Shutdown( void ) { };

			GameObject*	const	Owner( void ) const { return owner; }

		protected:
			GameObject*			owner;
		};
	}
}

#endif//__INGREDIENT