#include <memory>

#include "AmbientLight.h"
#include "IShader.h"
#include "GameObject.h"

using namespace Graphos::Core;
using namespace Graphos::Graphics;
using namespace Graphos::Math;


AmbientLight::AmbientLight( std::string name, Vector4 initColor, GameObject* owner )
	: IComponent( owner ),
	name( name ),
	color( initColor ),
	buffer( new gByte[size] ),
	dirty( true ) { }

AmbientLight::AmbientLight( std::string name, Vector4 initColor, gSize childSize, GameObject* owner )
	: IComponent( owner ),
	name( name ),
	color( initColor ),
	buffer( new gByte[childSize] ),
	dirty( true ) { }

void AmbientLight::Update( void )
{

}

void AmbientLight::Draw( IShader* shader )
{
	if( dirty )
	{
		// update buffer
		UpdateBuffer();
		dirty = false;
	}
 
	// set buffer in the shader
	shader->SetUniformBuffer( name, buffer, size );

}

void AmbientLight::Shutdown( void )
{
	delete [] buffer; 
}

/*
* Implementation 
*/
void AmbientLight::UpdateBuffer( void )
{
	memcpy( buffer, &color, size );
}

const gSize AmbientLight::size = sizeof( Vector4 );