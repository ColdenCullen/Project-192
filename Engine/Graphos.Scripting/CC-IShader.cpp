#include <cvv8\XTo.hpp>
#include <cvv8\properties.hpp>
#include "ClassMapper.h"
#include "IShader.h"

using namespace v8;
using namespace Graphos::Math;
using namespace Graphos::Graphics;

NAME_CLASS(IShader)

void cvv8::ClassCreator_SetupBindings<IShader>::Initialize( Handle<v8::Object> const & target )
{
	ClassCreator<IShader>& IShadercc( ClassCreator<IShader>::Instance() );
	if( IShadercc.IsSealed() )
	{
		IShadercc.AddClassTo( TypeName<IShader>::Value, target );
		return;
	}

	IShadercc
		( "destroy", ClassCreator<IShader>::DestroyObjectCallback )
		( "RegisterConstBuffer", MethodToInCa<IShader, void (std::string, ConstBuffer*), &IShader::RegisterConstBuffer>::Call )
		( "SetUniform", ConstMethodToInCa<const IShader, void (std::string, const int, ShaderType), &IShader::SetUniform>::Call )
		;

	// Proxy accessor/mutator functions as JS properties

	AccessorAdder Vector3acc( IShadercc.Prototype() );
	Vector3acc
		( "ModelMatrix",
			MethodToGetter<IShader, Matrix4& (void), &IShader::GetModelMatrix>::Get,
			MethodToSetter<IShader, void (const Matrix4&), &IShader::SetModelMatrix>::Set )
		( "ViewMatrix",
			MethodToGetter<IShader, Matrix4& (void), &IShader::GetViewMatrix>::Get,
			MethodToSetter<IShader, void (const Matrix4&), &IShader::SetViewMatrix>::Set )
		( "ProjectionMatrix",
			MethodToGetter<IShader, Matrix4& (void), &IShader::GetProjectionMatrix>::Get,
			MethodToSetter<IShader, void (const Matrix4&), &IShader::SetProjectionMatrix>::Set )
		( "ModelViewProjectionMatrix",
			MethodToGetter<IShader, Matrix4& (void), &IShader::GetModelViewProjectionMatrix>::Get,
			ThrowingSetter::Set )
		;

	// Set static methods
	Handle<Function> ctor( IShadercc.CtorFunction() );

	IShadercc.AddClassTo( TypeName<IShader>::Value, target );
};
