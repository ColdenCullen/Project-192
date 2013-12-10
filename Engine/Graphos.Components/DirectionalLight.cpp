#include "DirectionalLight.h"
#include "IShader.h"

using namespace Graphos::Core;
using namespace Graphos::Graphics;
using namespace Graphos::Math;

DirectionalLight::DirectionalLight( std::string name, Vector4 initDir, Vector4 initColor, GameObject* owner )
	: AmbientLight( name, initColor, size, owner ),
	direction( initDir ) 
{
	
}

void DirectionalLight::Draw( IShader* shader )
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

void DirectionalLight::UpdateBuffer( void )
{
	memcpy( buffer, &color, sizeof(Vector4) );
	memcpy( buffer + sizeof(Vector4), &direction, sizeof(Vector4) );
}

// The float is for extra padding when buffering to GPU
const gSize DirectionalLight::size = sizeof( Vector4 )*2;