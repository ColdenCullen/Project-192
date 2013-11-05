#ifndef __GAME
#define __GAME

#include "GraphosGame.h"
#include "GameObjectCollection.h"

namespace Project192
{
	class Game : public Graphos::Core::GraphosGame
	{
	public:
		Graphos::Core::GameObjectCollection
							objects;
		Graphos::Core::GameObject*
							cube;

		void				Initialize( void ) override;
		void				Update( void ) override;
		void				Draw( void ) override;
		void				Shutdown( void ) override;
	};
}

#endif//__GAME