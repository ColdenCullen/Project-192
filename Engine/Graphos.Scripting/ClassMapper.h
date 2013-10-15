#ifndef __CLASS_MAPPER
#define __CLASS_MAPPER

#include "ClassWrapper.h"

#include "Transform.h"
#include "CgShader.h"
#include "GameObject.h"
#include "Mesh.h"
#include "TimeController.h"
#include "Vector3.h"

using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Graphics;

WRAP_CLASS(Time,())
WRAP_CLASS(Transform,(CtorForwarder<Transform*( void )>))
WRAP_CLASS(CgShader,(CtorForwarder<CgShader*( std::string, std::string )>))
WRAP_CLASS(GameObject,(CtorForwarder<GameObject*( void )>))
WRAP_CLASS(Mesh,(CtorForwarder<Mesh*( std::string )>))
WRAP_CLASS(Vector3,(CtorForwarder<Vector3*()>,
					CtorForwarder<Vector3*( float, float, float )>,
					CtorForwarder<Vector3*( const Vector3& )>))

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
				//cvv8::ClassCreator<IShader>::SetupBindings( dest );
				cvv8::ClassCreator<CgShader>::SetupBindings( dest );
				cvv8::ClassCreator<GameObject>::SetupBindings( dest );
				cvv8::ClassCreator<Time>::SetupBindings( dest );
			}
		};
	}
}

#endif//__CLASS_MAPPER