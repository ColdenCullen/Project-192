//#ifndef __CC_Time
//#define __CC_Time
//
//#include "Time.h"
//
//#include <v8\v8.h>
//#include "cvv8\ClassCreator.hpp"
//
//using namespace Graphos::Core;
//
//namespace cvv8
//{
//	CVV8_TypeName_DECL((Time));
//
//	// Define Constructors
//	typedef Signature<Time (
//		CtorForwarder<Time*()>,
//		CtorForwarder<Time*( float, float, float )>,
//		CtorForwarder<Time*( const Time& )>
//		)> TimeCtors;
//
//	template <>
//	struct ClassCreator_InternalFields<Time>	: public ClassCreator_InternalFields_Base<Time> { };
//
//	template <>
//	struct ClassCreator_SearchPrototypeForThis<Time> : public Opt_Bool<true> { };
//
//	template <>
//	class ClassCreator_Factory<Time>
//		: public ClassCreator_Factory_NativeToJSMap<Time, CtorArityDispatcher<TimeCtors>> { };
//
//	template <>
//	struct ClassCreator_WeakWrap<Time>
//	{
//		static void PreWrap( v8::Persistent<v8::Object> const &, v8::Arguments const & ) { }
//		static void Wrap( v8::Persistent<v8::Object> const &, TypeInfo<Time>::NativeHandle ) { }
//		static void Unwrap( v8::Handle<v8::Object> const &, TypeInfo<Time>::NativeHandle ) { }
//	};
//
//	template <>
//	struct ClassCreator_SetupBindings<Time>
//	{
//		static void Initialize( v8::Handle<v8::Object> const & target );
//	};
//
//
//	template <>
//	struct JSToNative<Time> : public JSToNative_ClassCreator<Time> { };
//
//	template <>
//	struct NativeToJS<Time> : public NativeToJSMap<Time>
//	{
//		v8::Handle<v8::Value> operator()( const Time& v ) const;
//	};
//}
//
//#endif//__CC_Time