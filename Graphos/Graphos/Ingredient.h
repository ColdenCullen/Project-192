#ifndef __INGREDIENT
#define __INGREDIENT

namespace Graphos
{
	class GameObject;

	namespace Core
	{
		class Ingredient
		{
		public:
								Ingredient( GameObject* owner = nullptr ) : owner( owner ) { }
			virtual				~Ingredient( void ) { }

			virtual bool		Update( void ) = 0;
			virtual void		Draw( void ) = 0;
			virtual void		Shutdown( void ) = 0;

			GameObject*	const	Owner( void ) const { return owner; }

		protected:
			GameObject* owner;
		};
	}
}

#endif//__INGREDIENT