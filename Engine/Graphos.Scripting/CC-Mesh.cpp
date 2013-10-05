#include "CC-Mesh.h"

using namespace Graphos::Core;
using namespace Graphos::Graphics;

#include "cvv8\XTo.hpp"
#include "cvv8\properties.hpp"
#include "CgShader.h"

using namespace v8;

namespace cvv8
{
	CVV8_TypeName_IMPL((Mesh), "Mesh");

	void ClassCreator_SetupBindings<Mesh>::Initialize( Handle<v8::Object> const & target )
	{
		ClassCreator<Mesh>& Meshcc( ClassCreator<Mesh>::Instance() );
		if( Meshcc.IsSealed() )
		{
			Meshcc.AddClassTo( TypeName<Mesh>::Value, target );
			return;
		}

		Meshcc
			( "destroy", ClassCreator<Mesh>::DestroyObjectCallback )
			//( "Update", MethodToInCa<Mesh, void (void), &Mesh::Update>::Call )
			//( "Draw", MethodToInCa<Mesh, void (IShader*), &Mesh::Draw>::Call )
			;

		// Set static methods
		Handle<Function> ctor( Meshcc.CtorFunction() );
		//ctor->Set( String::New( "TripleProduct" ), FunctionTemplate::New( FunctionToInCa<Vector3 (const Vector3&, const Vector3&, const Vector3&), &Vector3::TripleProduct>::Call )->GetFunction() );

		Meshcc.AddClassTo( TypeName<Mesh>::Value, target );
	};
} /* namespace */
