#ifndef __CAMERA
#define __CAMERA

#include "GameObject.h"
#include "Component.h"
#include "Matrix4.h"

using namespace Graphos::Math;

namespace Graphos
{
	namespace Core
	{
		class Camera : public Component
		{
		public:
								Camera( GameObject* owner );
			
			bool				Update( void );
			void				Draw( void );
			void				Shutdown( void );

		private:
			Matrix4				viewMatrix;
		};
	}
}

#endif//__CAMERA