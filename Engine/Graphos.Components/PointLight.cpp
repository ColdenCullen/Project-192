#include "PointLight.h"
#include "IShader.h"

using namespace Graphos::Core;
using namespace Graphos::Graphics;
using namespace Graphos::Math;

PointLight::PointLight( std::string name, 
					Vector4 initPos, 
					gFloat initRange, 
					gFloat initConstAttenuation,
					gFloat initLinearAttenuation,
					gFloat initQuadAttenuation,
					Vector4 initColor, 
					GameObject* owner )
	: AmbientLight( name, initColor, size, owner ),
	position( initPos ),
	attenuation( Vector4( initConstAttenuation, 
						initLinearAttenuation, 
						initQuadAttenuation, 
						initRange ) ),
	constAttenuation( attenuation.x ),
	linearAttenuation( attenuation.y ),
	quadAttenuation( attenuation.z ),
	range( attenuation.w )
	{ 
		attenuation.w = 1;
	}

void PointLight::Draw( IShader* shader )
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

void PointLight::UpdateBuffer( void )
{
	memcpy( buffer, &color, sizeof(Vector4) );
	memcpy( buffer + sizeof(Vector4), &position, sizeof(Vector4) );
	memcpy( buffer + sizeof(Vector4)*2, &attenuation, sizeof(Vector4) );
}

const gSize PointLight::size = sizeof(Vector4)*3;