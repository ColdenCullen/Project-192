#ifndef __CC_TEXTURE
#define __CC_TEXTURE

#include "Texture.h"

#include <v8\v8.h>

#include <cvv8\ClassCreator.hpp>
#include "NativeToJSMap_Graphos.h"

using namespace Graphos::Core;

namespace cvv8
{
	CVV8_TypeName_DECL((Texture));

	// Define Constructors
	typedef Signature<Texture (
		CtorForwarder<Texture*( std::string )>
		)> TextureCtors;


	template <>
	class ClassCreator_Factory<Texture>
		: public ClassCreator_Factory_NativeToJSMap<Texture, CtorArityDispatcher<TextureCtors>> { };

	template <>
	struct ClassCreator_SetupBindings<Texture>
	{
		static void Initialize( v8::Handle<v8::Object> const & target );
	};

	template <>
	struct JSToNative<Texture> : public JSToNative_ClassCreator<Texture> { };

	template <>
	struct NativeToJS<Texture> : public NativeToJSMap_Graphos<Texture> { };
}

#endif//__CC_TEXTURE
