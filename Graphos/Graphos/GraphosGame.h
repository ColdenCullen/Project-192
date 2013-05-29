#ifndef __GRAPHOS_GAME
#define __GRAPHOS_GAME
/*
#include <unordered_map>

//#include "Camera.h"
#include "GameObject.h"
//#include "UserInterface.h"

using namespace std;

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
			virtual bool		Initialize( void ) = 0;
			virtual bool		Update( void ) = 0;
			virtual void		Draw( void ) = 0;
			virtual void		Shutdown( void ) = 0;
	
			unordered_map<unsigned int, GameObject>*
								objects;
	
			bool				objectsLoaded;
			//UserInterface*		ui;
			//Camera*				camera;
	
			void				LoadObjects( void );
			void				DeleteObjects( void );
	
		private:
			bool				Start( void );
			void				Stop( void );
		};
	}
}
*/

#endif//__GRAPHOS_GAME