#ifndef __INGREDIENT
#define __INGREDIENT

namespace Graphos
{
	namespace Core
	{
		// Forward declaration
		class GameObject;

		class IComponent
		{
		public:
								IComponent( GameObject* owner = nullptr ) : owner( owner ) { }
			virtual				~IComponent( void ) { }

			virtual bool		Update( void ) = 0;
			virtual void		Draw( void ) = 0;
			virtual void		Shutdown( void ) = 0;

			GameObject*	const	Owner( void ) const { return owner; }

		protected:
			GameObject*			owner;
		};
	}
}

#endif//__INGREDIENT