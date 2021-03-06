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
			
			void				Update( void );
			void				Draw( void );
			void				Shutdown( void );
			Math::Matrix4*		GetViewMatrix( void ) { return viewMatrix; }

			GameObject* const	Owner( void ) const { return owner; }

			const Math::Matrix4*
								GetViewMatrix( void ) const { return viewMatrix; }

		private:
			Math::Matrix4*		viewMatrix;
		};
	}
}

#endif//__CAMERA