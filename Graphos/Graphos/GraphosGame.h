#ifndef __GRAPHOS_GAME
#define __GRAPHOS_GAME

#include "UserInterface.h"
#include "Camera.h"

//#include <unordered_map>

namespace Graphos
{
	namespace Core
	{
		enum class GameState { Menu, Game, Reseting };
	
		class GraphosGame
		{
		public:
			GameState			CurrentState;
	
			void				Run( void );
			void				Reset( void );
	
		protected:
			virtual void		Initialize( void ) = 0;
			virtual bool		Update( void ) = 0;
			virtual void		Draw( void ) = 0;
			virtual void		Shutdown( void ) = 0;

			//std::unordered_map<std::string, GameObjectCollection> GOCList;

			UserInterface*		ui;
			Camera*				camera;
	
		private:
			bool				Start( void );
			void				Stop( void );
		};
	}
}

#endif//__GRAPHOS_GAME