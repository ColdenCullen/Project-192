#version 400

// Input variables
in vec3 inputPosition;
in vec2 inputTexCoord;

// Output variables
out vec2 texCoord;

// Uniforms
uniform mat4 modelViewProjection;

// Shader code
void main( void )
{
	//gl_Position = modelViewProjection * vec4( inputPosition, 1.0f );
	gl_Position = vec4( inputPosition, 1.0f );

	// Store texture coordinates for pixel shader
	texCoord = inputTexCoord;
}
