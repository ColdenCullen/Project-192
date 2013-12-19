#version 400

// Structs
struct DirectionalLight
{
	vec4 color;
	vec3 direction; // really a vec4 because OpenGL
};

struct AmbientLight
{
	vec4 color;
};

// In variables
in vec3 fPosition;
in vec2 fUV;
in vec3 fNormal;

// Uniforms
uniform sampler2D uShaderTexture;
uniform AmbientLight ambientLight = AmbientLight( vec4(.2,.2,.2,1.0) );
uniform DirectionalLight dirLight = DirectionalLight( vec4(1.0,1.0,1.0,1.0),vec3( -1.0, -1.0, 1.0 ) );

void main( void )
{
	vec4 texDiffuse = texture( uShaderTexture, fUV );
	vec4 texAmbient = texDiffuse;

	//*
	float ndotl = clamp( dot( fNormal, -dirLight.direction ), 0.0f, 1.0f );


	gl_FragColor = ( dirLight.color * ndotl * texDiffuse )
					+ (ambientLight.color * texAmbient );
	/*/
	gl_FragColor = texDiffuse;
	//*/
}
 