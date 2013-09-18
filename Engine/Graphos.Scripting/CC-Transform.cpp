#include "CC-Transform.h"
#include "CC-Vector3.h"

#include <cvv8\XTo.hpp>
#include <cvv8\Properties.hpp>
#include <cvv8\Arguments.hpp>

using namespace v8;

namespace cvv8
{
	CVV8_TypeName_IMPL((Transform), "Transform");

	void ClassCreator_SetupBindings<Transform>::Initialize( Handle<v8::Object> const & target )
	{
		ClassCreator<Transform>& Transformcc( ClassCreator<Transform>::Instance() );
		if( Transformcc.IsSealed() )
		{
			Transformcc.AddClassTo( TypeName<Transform>::Value, target );
			return;
		}

		Transformcc
			( "destroy", ClassCreator<Transform>::DestroyObjectCallback )
			( "Rotate",
				PredicatedInCaDispatcher<CVV8_TYPELIST((
				/*PredicatedInCa<
				ArgAt_IsA<0, const Quaternion&>,
				MethodToInCa<Transform, void (const Quaternion&), &Transform::Rotate>>,
				PredicatedInCa<
				Argv_Length<4>,
				MethodToInCa<Transform, void (const float, const float, const float, const float), &Transform::Rotate>>,*/
					PredicatedInCa<
						ArgAt_IsA<0, const Vector3&>,
						MethodToInCa<Transform, void (const Vector3&), &Transform::Rotate>>,
					PredicatedInCa<
						Argv_Length<3>,
						MethodToInCa<Transform, void (const float, const float, const float), &Transform::Rotate>>
				))>::Call )
			( "Translate",
				PredicatedInCaDispatcher<CVV8_TYPELIST((
					PredicatedInCa<
						ArgAt_IsA<0, const Vector3&>,
						MethodToInCa<Transform, void (const Vector3&), &Transform::Translate>>,
					PredicatedInCa<
						Argv_Length<3>,
						MethodToInCa<Transform, void (const float, const float, const float), &Transform::Translate>>
				))>::Call )
			( "Scale",
				PredicatedInCaDispatcher<CVV8_TYPELIST((
					PredicatedInCa<
						ArgAt_IsA<0, const Vector3&>,
						MethodToInCa<Transform, void (const Vector3&), &Transform::Scale>>,
					PredicatedInCa<
						Argv_Length<3>,
						MethodToInCa<Transform, void (const float, const float, const float), &Transform::Scale>>
				))>::Call )
			;

		// Proxy accessor/mutator functions as JS properties
		AccessorAdder Transformacc( Transformcc.Prototype() );
		Transformacc
			( "Position",
				ConstMethodToGetter<const Transform, const Vector3& (void), &Transform::Position>::Get,
				ThrowingSetter::Set )
			( "Rotation",
				ConstMethodToGetter<const Transform, const Vector3& (void), &Transform::Rotation>::Get,
				ThrowingSetter::Set )
			/*( "Scale",
				ConstMethodToGetter<const Transform, const Vector3& (void), &Transform::Scale>::Get,
				ThrowingSetter::Set )
			( "WorldMatrix",
				ConstMethodToGetter<const Transform, const Matrix4 (void), &Transform::WorldMatrix>::Get,
				ThrowingSetter::Set )
			( "RotationMatrix",
				ConstMethodToGetter<const Transform, const Matrix4 (void), &Transform::RotationMatrix>::Get,
				ThrowingSetter::Set )*/
			( "Right",
				ConstMethodToGetter<const Transform, const Vector3& (void), &Transform::GetRight>::Get,
				ThrowingSetter::Set )
			( "Up",
				ConstMethodToGetter<const Transform, const Vector3& (void), &Transform::GetUp>::Get,
				ThrowingSetter::Set )
			( "Forward",
				ConstMethodToGetter<const Transform, const Vector3& (void), &Transform::GetForward>::Get,
				ThrowingSetter::Set )
			;

		Transformcc.AddClassTo( TypeName<Transform>::Value, target );
	};

	Handle<Value> NativeToJS<Transform>::operator()( const Transform& v ) const
	{
		v8::Handle<v8::Object> toReturn;

		if( ( toReturn = GetJSObject( (void*)&v ) ).IsEmpty() )
		{	// If object does not exist in the JSMap, create it
			toReturn = ClassCreator<Transform>::Instance().NewInstance( 0, NULL )->ToObject();
			toReturn->SetInternalField( 0, External::New( (void*)&v ) );
			//toReturn->Set( String::New( "Position" ), CastToJS( v.Position() ) );
		}

		return toReturn;
	}
} /* namespace */