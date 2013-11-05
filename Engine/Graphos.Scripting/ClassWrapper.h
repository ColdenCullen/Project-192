#ifndef __CLASS_WRAPPER
#define __CLASS_WRAPPER

#include <v8/v8.h>
#include <cvv8/ClassCreator.hpp>

#define WRAP_CLASS(CLASS, CONSTRUCTORS)																		\
namespace cvv8 {																							\
	CVV8_TypeName_DECL((CLASS));																			\
	template<> class ClassCreator_Factory<CLASS>															\
		: public ClassCreator_Factory_NativeToJSMap<CLASS,CtorArityDispatcher<Signature<CLASS CONSTRUCTORS >>> { };			\
	template<> struct ClassCreator_SetupBindings<CLASS>														\
		{ static void Initialize( v8::Handle<v8::Object> const & target ); };								\
	template<> struct JSToNative<CLASS> : public JSToNative_ClassCreator<CLASS> { };						\
	template<> struct NativeToJS<CLASS> : public NativeToJSMap<CLASS>::NativeToJSImpl { };					\
}

#define NAME_CLASS(CLASS)																					\
namespace cvv8																								\
{																											\
	CVV8_TypeName_IMPL((CLASS), #CLASS);																	\
}

#endif//__CLASS_WRAPPER
