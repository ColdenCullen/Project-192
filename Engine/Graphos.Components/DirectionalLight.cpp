#include "DirectionalLight.h"
#include "IShader.h"

using namespace Graphos::Core;
using namespace Graphos::Graphics;
using namespace Graphos::Math;

DirectionalLight::DirectionalLight( std::string name, Vector3 initDir, Vector4 initColor, GameObject* owner )
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
	int bufferIndex = 0;
	memcpy( buffer, &color, sizeof( Vector4 ) );
	bufferIndex += sizeof( Vector4 );
	memcpy( buffer + bufferIndex, &direction, sizeof( Vector3 ) );
	
}

// The float is for extra padding when buffering to GPU
const gSize DirectionalLight::size = sizeof( Vector4 ) + sizeof( Vector3 ) + sizeof( float );