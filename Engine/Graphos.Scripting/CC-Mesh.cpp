#include <cvv8/XTo.hpp>
#include <cvv8/properties.hpp>
#include "ClassMapper.h"
#include "Mesh.h"

using namespace v8;
using namespace Graphos::Core;
using namespace Graphos::Graphics;

NAME_CLASS(Mesh);

void cvv8::ClassCreator_SetupBindings<Mesh>::Initialize( Handle<v8::Object> const & target )
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
