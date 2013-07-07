#ifndef __CAMERA
#define __CAMERA

#include "GameObject.h"
#include "IComponent.h"
#include "Matrix4.h"

namespace Graphos
{
	namespace Core
	{
		class Camera : public IComponent
		{
		public:
								Camera( GameObject* owner );
			
			bool				Update( void );
			void				Draw( void );
			void				Shutdown( void );

		private:
			Math::Matrix4		viewMatrix;
		};
	}
}

#endif//__CAMERA