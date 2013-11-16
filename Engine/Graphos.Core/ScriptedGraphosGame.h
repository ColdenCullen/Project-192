#ifndef __SCRIPTED_GRAPHOS_GAME
#define __SCRIPTED_GRAPHOS_GAME

#include "GraphosGame.h"
#include "GraphosBehavior.h"

namespace Graphos
{
	namespace Core
	{
		class ScriptedGraphosGame : public GraphosGame
		{
		public:
			void				Initialize( void ) override;
			void				Update( void ) override;
			void				Draw( void ) override;
			void				Shutdown( void ) override;

			GameObjectCollection
								objects;

		protected:
			GraphosBehavior*	script;

			gBool				useScript;
		};
	}
}

#endif//__SCRIPTED_GRAPHOS_GAME
