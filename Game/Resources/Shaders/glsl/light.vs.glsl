#version 400

// Structs
struct DirectionalLight
{
	vec3 direction;
	vec4 color;
}

// Input variables
in vec3 inPosition;
in vec2 inUV;
in vec3 inNormal;

// Output variables
out vec2 uv;
out vec3 normal;
out DirectionalLight light;

// Uniforms
uniform mat4 modelViewProj;
uniform mat4 model;

void main( void )
{
	gl_Position = modelViewProj * vec4( inPosition, 1.0f );

	uv = inUV;
	normal = normalize( model * vec4( inNormal, 1.0f )).xyz;
	light.direction = vec3( -1.0, -1.0f, 1.0f );
	light.color = vec4( 1.0, 1.0, 1.0, 1.0 );
}
