#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "GameObject.h"
#include "Ingredient.h"
#include "Matrix4.h"

using namespace Graphos::Core;
using namespace Graphos::Math;

namespace Graphos
{
	namespace Content
	{
		class Camera : public Ingredient
		{
		public:
								Camera( GameObject* owner );
			
			bool				Update( float deltaTime );
			void				Draw( void );
			void				Shutdown( void );

		private:
			Matrix4				viewMatrix;
		};
	}
}

#endif//_CAMERA_H_