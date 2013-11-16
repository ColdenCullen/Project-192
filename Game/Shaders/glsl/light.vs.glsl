#version 400

// Structs
struct DirectionalLight
{
	vec3 direction;
	vec4 color;
};

struct PointLight
{
	vec3 position;
	vec4 color;
};

// Input variables
in vec3 iPosition;
in vec2 iUV;
in vec3 iNormal;

// Output variables
out vec3 fPosition;
out vec2 fUV;
out vec3 fNormal;
out DirectionalLight fDirLights[2];

// Uniforms
uniform mat4 uModelViewProjection;
uniform mat4 uModelMatrix;
uniform DirectionalLight uDirLights[2];

void main( void )
{
	gl_Position = uModelViewProjection * vec4( iPosition, 1.0f );
	fPosition = gl_Position.xyz;

	fUV = iUV;
	fNormal = normalize( transpose(uModelMatrix) * vec4( iNormal, 1.0f ) ).xyz;
	fDirLights[0].direction = vec3( -1.0, -1.0f, 1.0f );
	fDirLights[0].color = vec4( 1.0, 1.0, 1.0, 1.0 );
}
