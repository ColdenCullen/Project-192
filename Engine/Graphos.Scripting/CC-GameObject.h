#ifndef __CC_GAME_OBJECT
#define __CC_GAME_OBJECT

#include "GameObject.h"

#include <v8\v8.h>

#include <cvv8\ClassCreator.hpp>
#include "NativeToJSMap_Graphos.h"

using namespace Graphos::Core;

namespace cvv8
{
	CVV8_TypeName_DECL((GameObject));

	// Define Constructors
	typedef Signature<GameObject (
		CtorForwarder<GameObject*( void )>//,
		//CtorForwarder<GameObject*( Graphos::Graphics::IShader* )>
		)> GameObjectCtors;


	template <>
	class ClassCreator_Factory<GameObject>
		: public ClassCreator_Factory_NativeToJSMap<GameObject, CtorArityDispatcher<GameObjectCtors>> { };

	template <>
	struct ClassCreator_SetupBindings<GameObject>
	{
		static void Initialize( v8::Handle<v8::Object> const & target );
	};

	template <>
	struct JSToNative<GameObject> : public JSToNative_ClassCreator<GameObject> { };

	template <>
	struct NativeToJS<GameObject> : public NativeToJSMap_Graphos<GameObject> { };
}

#endif//__CC_GAME_OBJECT
