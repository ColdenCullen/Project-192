#version 400

// In vars
in vec2 texCoord;

// Out vars
//out vec4 outputColor;

// Uniform vars
uniform sampler2D shaderTexture;

// Shader code
void main( void )
{
	vec4 textureColor;

	// Sample pixel color from texture using the sampler
	textureColor = texture( shaderTexture, texCoord );

	gl_FragColor = textureColor;
}
