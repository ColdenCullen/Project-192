#include <memory>

#include "AmbientLight.h"
#include "IShader.h"
#include "GameObject.h"

using namespace Graphos::Core;
using namespace Graphos::Graphics;
using namespace Graphos::Math;


AmbientLight::AmbientLight( std::string name, Vector4 initColor, GameObject* owner ) : IComponent( owner ),
	name( name ),
	color( initColor ),
	size( sizeof( Vector4 ) ),
	buffer( new gByte[size] ),
	dirty( true ) { }

void AmbientLight::Update( void )
{

}

void AmbientLight::Draw( IShader* shader )
{
	if( dirty )
	{
		// update buffer
		memcpy( buffer, &color, size );
		dirty = false;
	}

	// set buffer in the shader
	shader->SetUniformBuffer( name, buffer, size );

}

void AmbientLight::Shutdown( void )
{
	delete [] buffer; 
}