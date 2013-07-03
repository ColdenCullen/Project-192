#version 400

// Input variables
in vec3 inputPosition;
in vec2 inputTexCoord;
in vec3 inputNormal;

// Output variables
out vec2 texCoord;
out vec3 normal;

// Uniforms
uniform mat4 modelMatrix;
uniform mat4 cameraMatrix;
uniform mat4 projectionMatrix;

// Shader code
void main( void )
{
	// Set the position
	gl_Position = projectionMatrix * cameraMatrix * modelMatrix * vec4( inputPosition, 1.0f );

	// Store texture coordinates for pixel shader
	texCoord = inputTexCoord;

	// Calculate the normal vector against world matrix
	//normal = mat3( cameraMatrix ) * inputNormal;

	// Normalize
	normal = normalize( normal );
}