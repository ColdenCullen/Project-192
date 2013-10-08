#include "CC-GameObject.h"
#include "CC-Transform.h"

using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Graphics;

#include "cvv8\XTo.hpp"
#include "cvv8\properties.hpp"

using namespace v8;

namespace cvv8
{
	CVV8_TypeName_IMPL((GameObject), "GameObject");

	void ClassCreator_SetupBindings<GameObject>::Initialize( Handle<v8::Object> const & target )
	{
		ClassCreator<GameObject>& gameObjectcc( ClassCreator<GameObject>::Instance() );
		if( gameObjectcc.IsSealed() )
		{
			gameObjectcc.AddClassTo( TypeName<GameObject>::Value, target );
			return;
		}

		gameObjectcc
			( "destroy", ClassCreator<GameObject>::DestroyObjectCallback )
			//( "Update", MethodToInCa<GameObject, void (void), &GameObject::Update>::Call )
			//( "Draw", MethodToInCa<GameObject, void (void), &GameObject::Draw>::Call )
			//( "Cross", ConstMethodToInCa<const CgShader, CgShader (const CgShader&), &CgShader::Cross>::Call )
			//( "Add", ConstMethodToInCa<const CgShader, CgShader (const CgShader&), &CgShader::Add>::Call )
			;

		AccessorAdder gameObjectacc( gameObjectcc.Prototype() );
		gameObjectacc
			( "Transform",
			MemberToAccessors<GameObject, Transform, &GameObject::transform>::Get,
			ThrowingSetter::Set )
			;

		// Set static methods
		Handle<Function> ctor( gameObjectcc.CtorFunction() );
		//ctor->Set( String::New( "TripleProduct" ), FunctionTemplate::New( FunctionToInCa<Vector3 (const Vector3&, const Vector3&, const Vector3&), &Vector3::TripleProduct>::Call )->GetFunction() );

		gameObjectcc.AddClassTo( TypeName<GameObject>::Value, target );
	};
} /* namespace */
