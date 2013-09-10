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

		virtual void		Initialize( void ) override;
		virtual bool		Update( void ) override;
		virtual void		Draw( void ) override;
		virtual void		Shutdown( void ) override;
	};
}

#endif//__GAME