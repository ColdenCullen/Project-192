
//#include "lightStructs.hlsl"

struct AmbientLight
{
	float4 color			: COLOR1;
};

struct DirectionalLight
{
	float3 direction		: POSITION;
	float4 color			: COLOR0;
};

struct VertexToFragment
{
	float4 position			: SV_POSITION;
	float2 uv				: TEXCOORD0;
	float3 normal			: NORMAL;
	AmbientLight ambientLight;
	DirectionalLight dirLight;
};


Texture2D shaderTexture;
SamplerState sampleType;

float4 main( VertexToFragment input ) : SV_TARGET
{
	// DirectX and OpenGL have opposite y values for uv coordinates
	float4 texDiffuse = shaderTexture.Sample( sampleType, float2( input.uv.x, 1-input.uv.y ) );
	float4 texAmbient = texDiffuse;

	float intensity = saturate( dot( input.normal, -input.dirLight.direction ) );

	float4 color = (input.dirLight.color * intensity * texDiffuse)
				 + (input.ambientLight.color * texAmbient);

	return float4( color.xyz, 1.0f );
}