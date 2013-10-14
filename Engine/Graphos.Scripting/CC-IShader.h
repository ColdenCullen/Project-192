//#ifndef __CC_ISHADER
//#define __CC_ISHADER
//
//#include "IShader.h"
//
//#include <v8\v8.h>
//
//#include <cvv8\ClassCreator.hpp>
//#include "NativeToJSMap_Graphos.h"
//
//using namespace Graphos::Graphics;
//
//namespace cvv8
//{
//	CVV8_TypeName_DECL((IShader));
//
//	// Define Constructors
//	typedef Signature<IShader()> IShaderCtors;
//
//
//	template <>
//	class ClassCreator_Factory<IShader>
//		: public ClassCreator_Factory_NativeToJSMap<IShader, CtorArityDispatcher<IShaderCtors>> { };
//
//	template <>
//	struct ClassCreator_SetupBindings<IShader>
//	{
//		static void Initialize( v8::Handle<v8::Object> const & target );
//	};
//
//	template <>
//	struct JSToNative<IShader> : public JSToNative_ClassCreator<IShader> { };
//
//	template <>
//	struct NativeToJS<IShader> : public NativeToJSMap_Graphos<IShader> { };
//}
//
//#endif//__CC_ISHADER
