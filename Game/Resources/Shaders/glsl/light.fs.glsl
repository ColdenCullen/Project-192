#version 400

// Structs
struct DirectionalLight
{
	vec3 direction;
	vec4 color;
};

// In variables
in vec3 fPosition;
in vec2 fUV;
in vec3 fNormal;
in DirectionalLight fDirLights[2];

// Uniforms
uniform sampler2D uShaderTexture;

void main( void )
{
	vec4 texDiffuse = texture( uShaderTexture, fUV );

	//*
	float ndotl = clamp( dot( fNormal, -fDirLights[0].direction ), 0.0f, 1.0f );

	vec4 color = fDirLights[0].color * ndotl;

	color = color * texDiffuse;

	gl_FragColor = vec4( color.xyz, 1.0f );
	/*/
	gl_FragColor = texDiffuse;
	//*/
}
 