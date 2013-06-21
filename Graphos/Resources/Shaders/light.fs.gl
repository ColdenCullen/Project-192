#version 400

// In vars
in vec2 texCoord;
in vec3 normal;

// Out vars
out vec4 outputColor;

// Uniform vars
uniform sampler2D shaderTexture;
uniform vec3 lightDirection;
uniform vec4 diffuseLightColor;

// Shader code
void main( void )
{
	vec4 textureColor;
	vec3 lightDir;
	float lightIntensity;

	// Sample pixel color from texture using the sampler
	textureColor = texture( shaderTexture, texCoord );

	outputColor = textureColor;

	// Calculate light values

	// Invert light direction for maths
	lightDir = -lightDirection;

	// Calculate intensity
	lightIntensity = clamp( dot( normal, lightDir ), 0.0f, 1.0f );

	// Determine final difuse color
	outputColor = clamp( diffuseLightColor * lightIntensity, 0.0f, 1.0f );

	// Combine light with pixel color to get final color
	outputColor = outputColor * textureColor;
}