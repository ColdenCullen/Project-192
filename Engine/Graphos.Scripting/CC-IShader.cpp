//#include "CC-IShader.h"
//
//using namespace Graphos::Core;
//using namespace Graphos::Graphics;
//
//#include "cvv8\XTo.hpp"
//#include "cvv8\properties.hpp"
//
//using namespace v8;
//
//namespace cvv8
//{
//	CVV8_TypeName_IMPL((IShader), "IShader");
//
//	void ClassCreator_SetupBindings<IShader>::Initialize( Handle<v8::Object> const & target )
//	{
//		ClassCreator<IShader>& IShadercc( ClassCreator<IShader>::Instance() );
//		if( IShadercc.IsSealed() )
//		{
//			IShadercc.AddClassTo( TypeName<IShader>::Value, target );
//			return;
//		}
//
//		IShadercc
//			( "destroy", ClassCreator<IShader>::DestroyObjectCallback )
//			//( "Draw", ConstMethodToInCa<const IShader, void (const Mesh&), &IShader::Draw>::Call )
//			//( "BindTexture", ConstMethodToInCa<const IShader, void (const Texture&), &IShader::BindTexture>::Call )
//			//( "Cross", ConstMethodToInCa<const IShader, IShader (const IShader&), &IShader::Cross>::Call )
//			//( "Add", ConstMethodToInCa<const IShader, IShader (const IShader&), &IShader::Add>::Call )
//			;
//
//		// Set static methods
//		Handle<Function> ctor( IShadercc.CtorFunction() );
//		//ctor->Set( String::New( "TripleProduct" ), FunctionTemplate::New( FunctionToInCa<Vector3 (const Vector3&, const Vector3&, const Vector3&), &Vector3::TripleProduct>::Call )->GetFunction() );
//
//		IShadercc.AddClassTo( TypeName<IShader>::Value, target );
//	};
//} /* namespace */
