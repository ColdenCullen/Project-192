#ifndef __GRAPHOS_MOTION_STATE
#define __GRAPHOS_MOTION_STATE

#include "IComponent.h"

#include <LinearMath\btMotionState.h>

namespace Graphos
{
	namespace Physics
	{
		class GraphosMotionState : public Core::IComponent, public btMotionState
		{
		public:
			GraphosMotionState( Core::GameObject* owner );

			void Shutdown( void ) override;

			void getWorldTransform( btTransform& worldTrans ) const override;

			void setWorldTransform( const btTransform& worldTrans ) override;

		};
	}
}

#endif