#include <cvv8\XTo.hpp>
#include <cvv8\properties.hpp>
#include "ClassMapper.h"
#include "IShader.h"

using namespace v8;
using namespace Graphos::Math;
using namespace Graphos::Graphics;

NAME_CLASS(ConstBuffer)

void cvv8::ClassCreator_SetupBindings<ConstBuffer>::Initialize( Handle<v8::Object> const & target )
{
	ClassCreator<ConstBuffer>& ConstBuffercc( ClassCreator<ConstBuffer>::Instance() );
	if( ConstBuffercc.IsSealed() )
	{
		ConstBuffercc.AddClassTo( TypeName<ConstBuffer>::Value, target );
		return;
	}

	ConstBuffercc
		( "destroy", ClassCreator<ConstBuffer>::DestroyObjectCallback )
		( "AddProperty", MethodToInCa<ConstBuffer, void (std::string, std::size_t), &ConstBuffer::AddProperty>::Call )
		;

	// Set static methods
	Handle<Function> ctor( ConstBuffercc.CtorFunction() );

	ConstBuffercc.AddClassTo( TypeName<ConstBuffer>::Value, target );
}
