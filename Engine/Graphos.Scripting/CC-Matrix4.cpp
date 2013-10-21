#include <cvv8\XTo.hpp>
#include <cvv8\properties.hpp>
#include "ClassMapper.h"
#include "Matrix4.h"

using namespace v8;
using namespace Graphos::Math;

NAME_CLASS(Matrix4)

void cvv8::ClassCreator_SetupBindings<Matrix4>::Initialize( Handle<v8::Object> const & target )
{
	ClassCreator<Matrix4>& Matrix4cc( ClassCreator<Matrix4>::Instance() );
	if( Matrix4cc.IsSealed() )
	{
		Matrix4cc.AddClassTo( TypeName<Matrix4>::Value, target );
		return;
	}

	Matrix4cc
		( "destroy", ClassCreator<Matrix4>::DestroyObjectCallback )
		( "Mul", ConstMethodToInCa<const Matrix4, Matrix4 (const Matrix4&), &Matrix4::Mul>::Call )
		( "Add", ConstMethodToInCa<const Matrix4, Matrix4 (const Matrix4&), &Matrix4::Add>::Call )
		( "Equals", ConstMethodToInCa<const Matrix4, bool (const Matrix4&), &Matrix4::Equals>::Call )
		( "Mul", ConstMethodToInCa<const Matrix4, Vector3 (const Vector3&), &Matrix4::Mul>::Call )
		;

	// Proxy accessor/mutator functions as JS properties
/*	AccessorAdder Matrix4acc( Matrix4cc.Prototype() );
	Matrix4acc
		( "dataArray",
			MemberToAccessors<const Matrix4, ??? */

	// Set static methods
	Handle<Function> ctor( Matrix4cc.CtorFunction() );

	Matrix4cc.AddClassTo( TypeName<Matrix4>::Value, target );

	
};
