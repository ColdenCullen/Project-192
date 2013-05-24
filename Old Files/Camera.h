#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "ShaderController.h"
#include "GameObject.h"
#include "Ingredient.h"
#include "Matrix.h"
#include "Vector3.h"

using namespace Graphos;
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
			Matrix				viewMatrix;
		};
	}
}

#endif//_CAMERA_H_