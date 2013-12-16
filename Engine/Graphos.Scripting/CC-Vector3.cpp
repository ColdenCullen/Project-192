#include <cvv8\XTo.hpp>
#include <cvv8\properties.hpp>
#include "ClassMapper.h"
#include "Vector3.h"

using namespace v8;
using namespace Graphos::Core;

NAME_CLASS(Vector3)

void cvv8::ClassCreator_SetupBindings<Vector3>::Initialize( Handle<v8::Object> const & target )
{
	ClassCreator<Vector3>& Vector3cc( ClassCreator<Vector3>::Instance() );
	if( Vector3cc.IsSealed() )
	{
		Vector3cc.AddClassTo( TypeName<Vector3>::Value, target );
		return;
	}

	Vector3cc
		( "destroy", ClassCreator<Vector3>::DestroyObjectCallback )
		( "Equals", ConstMethodToInCa<const Vector3, gBool (const Vector3&), &Vector3::Equals>::Call )
		( "Dot", ConstMethodToInCa<const Vector3, gFloat (const Vector3&), &Vector3::Dot>::Call )
		( "Cross", ConstMethodToInCa<const Vector3, Vector3 (const Vector3&), &Vector3::Cross>::Call )
		( "Add", ConstMethodToInCa<const Vector3, Vector3 (const Vector3&), &Vector3::Add>::Call )
		( "Multiply", ConstMethodToInCa<const Vector3, Vector3 (const gFloat), &Vector3::operator*>::Call )
		;

	// Proxy accessor/mutator functions as JS properties
	AccessorAdder Vector3acc( Vector3cc.Prototype() );
	Vector3acc
		( "x",
			MemberToAccessors<const Vector3, gFloat, &Vector3::x>::Get,
			MemberToAccessors<const Vector3, gFloat, &Vector3::x>::Set )
		( "y",
			MemberToAccessors<const Vector3, gFloat, &Vector3::y>::Get,
			MemberToAccessors<const Vector3, gFloat, &Vector3::y>::Set )
		( "z",
			MemberToAccessors<const Vector3, gFloat, &Vector3::z>::Get,
			MemberToAccessors<const Vector3, gFloat, &Vector3::z>::Set )
		( "Inverse",
			ConstMethodToGetter<const Vector3, Vector3 (void), &Vector3::Inverse>::Get,
			ThrowingSetter::Set )
		;

	// Set static methods
	Handle<Function> ctor( Vector3cc.CtorFunction() );
	ctor->Set( String::New( "TripleProduct" ), FunctionTemplate::New( FunctionToInCa<Vector3 (const Vector3&, const Vector3&, const Vector3&), &Vector3::TripleProduct>::Call )->GetFunction() );
	ctor->SetAccessor( String::New( "Right" ), VarToAccessors<const Vector3, &Vector3::Right>::Get );
	ctor->SetAccessor( String::New( "Up" ), VarToAccessors<const Vector3, &Vector3::Up>::Get );
	ctor->SetAccessor( String::New( "Forward" ),VarToAccessors<const Vector3, &Vector3::Forward>::Get );

	Vector3cc.AddClassTo( TypeName<Vector3>::Value, target );
};

