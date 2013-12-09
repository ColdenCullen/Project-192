#include "PointLight.h"
#include "IShader.h"

using namespace Graphos::Core;
using namespace Graphos::Graphics;
using namespace Graphos::Math;

PointLight::PointLight( std::string name, Vector3 initPos, gFloat initFallOffRadius, Vector4 initColor, GameObject* owner )
	: AmbientLight( name, initColor, size, owner ),
	position( initPos ),
	fallOffRadius( initFallOffRadius ) { }

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
	// TODO
}

// TODO: do this
const gSize PointLight::size = 0;