#version 400

// Structs
struct DirectionalLight
{
	vec3 direction;
	vec4 color;
};

// In variables
in vec2 uv;
in vec3 normal;
in DirectionalLight light;

// Uniforms
uniform sampler2D shaderTexture;

void main( void )
{
	vec4 texDiffuse = texture( shaderTexture, uv );

	float ndotl = clamp( dot( normal, -light.direction ), 0.0f, 1.0f );

	vec4 color = light.color * ndotl;

	color = color * texDiffuse;

	gl_FragColor = vec4( color.xyz, 1.0f );
}
 