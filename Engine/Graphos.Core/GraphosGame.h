#ifndef __GRAPHOS_GAME
#define __GRAPHOS_GAME

#include "UserInterface.h"
#include "Camera.h"

namespace Graphos
{
	namespace Core
	{
		enum GameState { Menu = 0, Game = 1, Reseting = 2 };
	
		class GraphosGame
		{
		public:
			GameState			CurrentState;
	
			void				Run( void );
			void				Reset( void );
			void				Exit( void );

			static Camera*		camera;

		protected:
			virtual void		Initialize( void );
			virtual void		Update( void );
			virtual void		Draw( void );
			virtual void		Shutdown( void );

			//std::unordered_map<std::string, GameObjectCollection> GOCList;

			UserInterface*		ui;
	
		private:
			bool				quit;

			void				Start( void );
			void				Stop( void );
		};
	}
}

#endif//__GRAPHOS_GAME