#ifndef __CLASS_CONVERTER
#define __CLASS_CONVERTER

#include "Transform.h"
#include "Vector2.h"
#include "Vector3.h"

#include <cvv8\ClassCreator.hpp>
#include <cvv8\v8-convert.hpp>

using namespace Graphos::Math;

namespace cvv8
{
	// Declare types
	CVV8_TypeName_DECL((Transform));
	CVV8_TypeName_DECL((Vector2));
	CVV8_TypeName_DECL((Vector3));

	// Implement factories
	template<>
	class ClassCreator_Factory<Transform> :
		public ClassCreator_Factory_Dispatcher<Transform, CtorArityDispatcher<Signature<Transform
			(
				CtorForwarder<Transform*()>,
				CtorForwarder<Transform*( const Transform& )>
			)
		>>>
	{};
	template<>
	class ClassCreator_Factory<Vector2> :
		public ClassCreator_Factory_Dispatcher<Vector2, CtorArityDispatcher<Signature<Vector2
			(
				CtorForwarder<Vector2*()>,
				CtorForwarder<Vector2*( const float[2] )>,
				CtorForwarder<Vector2*( float, float )>,
				CtorForwarder<Vector2*( const Vector2& )>
			)
		>>>
	{};
	template<>
	class ClassCreator_Factory<Vector3> :
		public ClassCreator_Factory_Dispatcher<Vector3, CtorArityDispatcher<Signature<Vector3
			(
				CtorForwarder<Vector3*()>,
				CtorForwarder<Vector3*( const float[3] )>,
				CtorForwarder<Vector3*( float, float, float )>,
				CtorForwarder<Vector3*( const Vector3& )>
			)
		>>>
	{};

	// Implement converters
	template<>
	struct JSToNative<Transform> : JSToNative_ClassCreator<Transform>
	{};
	template<>
	struct JSToNative<Transform> : JSToNative_ClassCreator<Vector2>
	{};
	template<>
	struct JSToNative<Transform> : JSToNative_ClassCreator<Vector3>
	{};

	void BindGraphosTypes( v8::Handle<v8::Object> dest )
	{
		//TODO: Explore options, use this? https://code.google.com/p/v8-juice/wiki/V8Convert_ClassCreator

		typedef ClassCreator<Transform> TransformCC;
		TransformCC& tcc(TransformCC::Instance());
		if( tcc.IsSealed() ) { // the binding was already initialized.
			tcc.AddClassTo( TypeName<Transform>::Value, dest );
			return;
		}
		// Else initialize the bindings...
		tcc
			( "destroy", TransformCC::DestroyObjectCallback )
			( "Position", MethodToInCa<Transform, Vector3 (void) const, &Transform::Position>::Call )
			( "Rotation", MethodToInCa<Transform, Vector3 (void) const, &Transform::Rotation>::Call )
			( "Scale", MethodToInCa<Transform, Vector3 (void) const, &Transform::Scale>::Call )
			.AddClassTo( TypeName<Transform>::Value, dest );
	}
}

#endif//__CLASS_CONVERTER