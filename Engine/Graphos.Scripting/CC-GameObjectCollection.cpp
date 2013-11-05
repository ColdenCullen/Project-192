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
	ClassCreator<GameObjectCollection>& gameObjectcc( ClassCreator<GameObjectCollection>::Instance() );
	if( gameObjectcc.IsSealed() )
	{
		gameObjectcc.AddClassTo( TypeName<GameObjectCollection>::Value, target );
		return;
	}

	gameObjectcc
		( "destroy", ClassCreator<GameObjectCollection>::DestroyObjectCallback )
		( "LoadObjects", MethodToInCa<GameObjectCollection, void( std::string ), &GameObjectCollection::LoadObjects>::Call )
		( "ClearObjects", MethodToInCa<GameObjectCollection, void( void ), &GameObjectCollection::ClearObjects>::Call )
		( "CreateObject", MethodToInCa<GameObjectCollection, unsigned int( std::string, IShader* ), &GameObjectCollection::CreateObject>::Call )
		( "GetObjectById", MethodToInCa<GameObjectCollection, GameObject*( unsigned int ), &GameObjectCollection::GetObjectById>::Call )
		( "GetObjectByName", MethodToInCa<GameObjectCollection, GameObject*( std::string ), &GameObjectCollection::GetObjectByName>::Call )
		( "RemoveObjectById", MethodToInCa<GameObjectCollection, void( unsigned int ), &GameObjectCollection::RemoveObjectById>::Call )
		( "RemoveObjectByName", MethodToInCa<GameObjectCollection, void( std::string ), &GameObjectCollection::RemoveObjectByName>::Call )
		//( "Draw", MethodToInCa<GameObject, void (void), &GameObject::Draw>::Call )
		;

	AccessorAdder gameObjectacc( gameObjectcc.Prototype() );
	//gameObjectacc
	//	( "Transform",
	//	MemberToAccessors<GameObject, Transform*, &GameObjectCollection::transform>::Get,
	//	ThrowingSetter::Set )
	//	;

	// Set static methods
	Handle<Function> ctor( gameObjectcc.CtorFunction() );
	//ctor->Set( String::New( "TripleProduct" ), FunctionTemplate::New( FunctionToInCa<Vector3 (const Vector3&, const Vector3&, const Vector3&), &Vector3::TripleProduct>::Call )->GetFunction() );

	gameObjectcc.AddClassTo( TypeName<GameObject>::Value, target );
};
