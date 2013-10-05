#include "CC-Texture.h"

using namespace Graphos::Core;
using namespace Graphos::Graphics;

#include <cvv8\XTo.hpp>
#include <cvv8\properties.hpp>
#include "IComponent.h"

using namespace v8;

namespace cvv8
{
	CVV8_TypeName_IMPL((Texture), "Texture");

	void ClassCreator_SetupBindings<Texture>::Initialize( Handle<v8::Object> const & target )
	{
		ClassCreator<Texture>& Texturecc( ClassCreator<Texture>::Instance() );
		if( Texturecc.IsSealed() )
		{
			Texturecc.AddClassTo( TypeName<Texture>::Value, target );
			return;
		}

		Texturecc
			( "destroy", ClassCreator<Texture>::DestroyObjectCallback )
			//( "Update", MethodToInCa<IComponent, void (void), &Texture::Update>::Call )
			//( "Draw", MethodToInCa<Texture, void (IShader*), &Texture::Draw>::Call )
			;

		// Set static methods
		Handle<Function> ctor( Texturecc.CtorFunction() );
		//ctor->Set( String::New( "TripleProduct" ), FunctionTemplate::New( FunctionToInCa<Vector3 (const Vector3&, const Vector3&, const Vector3&), &Vector3::TripleProduct>::Call )->GetFunction() );

		Texturecc.AddClassTo( TypeName<Texture>::Value, target );
	};
} /* namespace */
