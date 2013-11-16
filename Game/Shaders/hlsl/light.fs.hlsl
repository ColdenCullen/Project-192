
//#include "lightStructs.hlsl"

struct DirectionalLight
{
	float3 direction		: POSITION;
	float4 color			: COLOR;
};

struct VertexToFragment
{
	float4 position			: SV_POSITION;
	float2 uv				: TEXCOORD0;
	float3 normal			: NORMAL;
	DirectionalLight light;
};


Texture2D shaderTexture;
SamplerState sampleType;

float4 main( VertexToFragment input ) : SV_TARGET
{
	// DirectX and OpenGL have opposite y values for uv coordinates
	float4 texDiffuse = shaderTexture.Sample( sampleType, float2( input.uv.x, 1-input.uv.y ) );

	float ndotl = saturate( dot( input.normal, -input.light.direction ) );

	float4 color = input.light.color * ndotl;
	color = color * texDiffuse;

	return float4( color.xyz, 1.0f );
}