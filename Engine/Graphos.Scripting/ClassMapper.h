#ifndef __CLASS_MAPPER
#define __CLASS_MAPPER

#include "ClassWrapper.h"

#include "Transform.h"
#include "GameObject.h"
#include "Mesh.h"
#include "TimeController.h"
#include "Vector3.h"
#include "Camera.h"

using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Graphics;

WRAP_CLASS(Time,())
WRAP_CLASS(Transform,(CtorForwarder<Transform*( void )>))
WRAP_CLASS(GameObject,(CtorForwarder<GameObject*( void )>))
WRAP_CLASS(Mesh,(CtorForwarder<Mesh*( std::string )>))
WRAP_CLASS(Vector3,(CtorForwarder<Vector3*( void )>,
					CtorForwarder<Vector3*( float, float, float )>,
					CtorForwarder<Vector3*( const Vector3& )>))
WRAP_CLASS(Matrix4,(CtorForwarder<Matrix4*( void )>))//,
				//	CtorForwarder<Matrix4*( float, float, float, float,
				//							float, float, float, float,
				//							float, float, float, float,
				//							float, float, float, float )>)) 
WRAP_CLASS(Camera,(CtorForwarder<Camera*( GameObject* )>))

namespace Graphos
{
	namespace Scripting
	{
		class ClassMapper
		{
		public:
			static void BindGraphosTypes( v8::Handle<v8::Object>& dest )
			{
				//cvv8::ClassCreator<Mesh>::SetupBindings( dest );
				//cvv8::ClassCreator<Texture>::SetupBindings( dest );
				cvv8::ClassCreator<Transform>::SetupBindings( dest );
				cvv8::ClassCreator<Vector3>::SetupBindings( dest );
				cvv8::ClassCreator<Matrix4>::SetupBindings( dest );
				//cvv8::ClassCreator<IShader>::SetupBindings( dest );
				cvv8::ClassCreator<GameObject>::SetupBindings( dest );
				cvv8::ClassCreator<Time>::SetupBindings( dest );
				cvv8::ClassCreator<Camera>::SetupBindings( dest );
			}
		};
	}
}

#endif//__CLASS_MAPPER