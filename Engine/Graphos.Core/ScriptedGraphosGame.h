#ifndef __SCRIPTED_GRAPHOS_GAME
#define __SCRIPTED_GRAPHOS_GAME

#include "GraphosGame.h"
#include "Script.h"

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

			Graphos::Core::GameObjectCollection
								objects;

		protected:
			Script*				script;

			bool				useScript;
		};
	}
}

#endif//__SCRIPTED_GRAPHOS_GAME
