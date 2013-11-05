#include <cvv8/XTo.hpp>
#include <cvv8/properties.hpp>
#include "ClassMapper.h"
#include "GameObjectCollection.h"

using namespace v8;
using namespace Graphos::Core;
using namespace Graphos::Math;
using namespace Graphos::Graphics;

NAME_CLASS(GameObjectCollection)

void cvv8::ClassCreator_SetupBindings<GameObjectCollection>::Initialize( Handle<v8::Object> const & target )
{
	ClassCreator<GameObjectCollection>& GameObjectCollectioncc( ClassCreator<GameObjectCollection>::Instance() );
	if( GameObjectCollectioncc.IsSealed() )
	{
		GameObjectCollectioncc.AddClassTo( TypeName<GameObjectCollection>::Value, target );
		return;
	}

	GameObjectCollectioncc
		( "destroy", ClassCreator<GameObjectCollection>::DestroyObjectCallback )
		( "LoadObjects", MethodToInCa<GameObjectCollection, void( std::string ), &GameObjectCollection::LoadObjects>::Call )
		( "ClearObjects", MethodToInCa<GameObjectCollection, void( void ), &GameObjectCollection::ClearObjects>::Call )
		//( "CreateObject", MethodToInCa<GameObjectCollection, unsigned int( std::string, IShader* ), &GameObjectCollection::CreateObject>::Call )
		( "GetObjectById", MethodToInCa<GameObjectCollection, GameObject*( unsigned int ), &GameObjectCollection::GetObjectById>::Call )
		( "GetObjectByName", MethodToInCa<GameObjectCollection, GameObject*( std::string ), &GameObjectCollection::GetObjectByName>::Call )
		( "RemoveObjectById", MethodToInCa<GameObjectCollection, void( unsigned int ), &GameObjectCollection::RemoveObjectById>::Call )
		( "RemoveObjectByName", MethodToInCa<GameObjectCollection, void( std::string ), &GameObjectCollection::RemoveObjectByName>::Call )
		( "Update", MethodToInCa<GameObjectCollection, void( void ), &GameObjectCollection::Update>::Call )
		( "Draw", MethodToInCa<GameObjectCollection, void( void ), &GameObjectCollection::Draw>::Call )
		//( "Draw", MethodToInCa<GameObject, void (void), &GameObject::Draw>::Call )
		;

	//AccessorAdder GameObjectCollectionacc( GameObjectCollectioncc.Prototype() );
	//GameObjectCollectionacc
	//	( "Transform",
	//		MemberToAccessors<GameObjectCollection, Transform*, &GameObjectCollection::transform>::Get,
	//		ThrowingSetter::Set )
	//	;

	// Set static methods
	Handle<Function> ctor( GameObjectCollectioncc.CtorFunction() );
	//ctor->Set( String::New( "TripleProduct" ), FunctionTemplate::New( FunctionToInCa<Vector3 (const Vector3&, const Vector3&, const Vector3&), &Vector3::TripleProduct>::Call )->GetFunction() );

	GameObjectCollectioncc.AddClassTo( TypeName<GameObjectCollection>::Value, target );
};


