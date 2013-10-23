#include "Scope.h"

using namespace Graphos::Memory;

Scope::Scope( void ) : currentId( 0 )
{
	current.push( this );
}

Scope::~Scope( void )
{
	if( current.top() !=  this )
		throw std::logic_error( "Cannot delete scope if it is not the top scope." );

	for( auto handle : handles )
	{
		handle.second->Delete();
	}

	handles.clear();

	current.pop();
}

std::stack<Scope*> Scope::current;
