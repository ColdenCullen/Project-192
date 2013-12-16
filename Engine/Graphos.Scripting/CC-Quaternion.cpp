#include <cvv8\XTo.hpp>
#include <cvv8\properties.hpp>
#include "ClassMapper.h"
#include "Quaternion.h"

using namespace v8;
using namespace Graphos::Core;

NAME_CLASS(Quaternion)

void cvv8::ClassCreator_SetupBindings<Quaternion>::Initialize( Handle<v8::Object> const & target )
{
	ClassCreator<Quaternion>& Quaternioncc( ClassCreator<Quaternion>::Instance() );
	if( Quaternioncc.IsSealed() )
	{
		Quaternioncc.AddClassTo( TypeName<Quaternion>::Value, target );
		return;
	}

	Quaternioncc
		( "destroy", ClassCreator<Quaternion>::DestroyObjectCallback )
		( "Equals", ConstMethodToInCa<const Quaternion, gBool (const Quaternion&), &Quaternion::operator==>::Call )
		( "Multiply", ConstMethodToInCa<const Quaternion, Quaternion (const Quaternion&), &Quaternion::operator*>::Call )
		;

	// Proxy accessor/mutator functions as JS properties
	AccessorAdder Quaternionacc( Quaternioncc.Prototype() );
	Quaternionacc
		( "x",
		MemberToAccessors<const Quaternion, gFloat, &Quaternion::x>::Get,
		MemberToAccessors<const Quaternion, gFloat, &Quaternion::x>::Set )
		( "y",
		MemberToAccessors<const Quaternion, gFloat, &Quaternion::y>::Get,
		MemberToAccessors<const Quaternion, gFloat, &Quaternion::y>::Set )
		( "z",
		MemberToAccessors<const Quaternion, gFloat, &Quaternion::z>::Get,
		MemberToAccessors<const Quaternion, gFloat, &Quaternion::z>::Set )
		( "w",
		MemberToAccessors<const Quaternion, gFloat, &Quaternion::w>::Get,
		MemberToAccessors<const Quaternion, gFloat, &Quaternion::w>::Set )
		/*( "Axis",
		MemberToAccessors<const Quaternion, Vector3, &Quaternion::axis>::Get,
		MemberToAccessors<const Quaternion, Vector3, &Quaternion::axis>::Set )*/
		;

	Quaternioncc.AddClassTo( TypeName<Quaternion>::Value, target );
};
