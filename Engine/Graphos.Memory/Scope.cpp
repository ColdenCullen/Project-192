#include "Scope.h"

using namespace Graphos::Memory;

Scope::Scope( void )
{
	current.push( this );
}

Scope::~Scope( void )
{
	for( auto handle : handles )
	{
		delete handle;
	}

	handles.clear();

	current.pop();
}
