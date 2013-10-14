#ifndef __CC_MESH
#define __CC_MESH

#include "Mesh.h"

#include <v8\v8.h>

#include <cvv8\ClassCreator.hpp>
#include "NativeToJSMap_Graphos.h"

using namespace Graphos::Core;

namespace cvv8
{
	CVV8_TypeName_DECL((Mesh));

	// Define Constructors
	typedef Signature<Mesh (
		CtorForwarder<Mesh*( std::string )>
		)> MeshCtors;


	template <>
	class ClassCreator_Factory<Mesh>
		: public ClassCreator_Factory_NativeToJSMap<Mesh, CtorArityDispatcher<MeshCtors>> { };

	template <>
	struct ClassCreator_SetupBindings<Mesh>
	{
		static void Initialize( v8::Handle<v8::Object> const & target );
	};

	template <>
	struct JSToNative<Mesh> : public JSToNative_ClassCreator<Mesh> { };

	template <>
	struct NativeToJS<Mesh> : public NativeToJSMap_Graphos<Mesh> { };
}

#endif//__CC_MESH
