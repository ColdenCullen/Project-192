#ifndef __GAME
#define __GAME

#include "GraphosGame.h"

namespace Project192
{
	class Game : public Graphos::Core::GraphosGame
	{
	public:
		Game( void );
		~Game( void );

		virtual bool Initialize( void ) override;
		virtual bool Update( void ) override;
		virtual void Draw( void ) override;
		virtual void Shutdown( void ) override;
	};
}

#endif//__GAME