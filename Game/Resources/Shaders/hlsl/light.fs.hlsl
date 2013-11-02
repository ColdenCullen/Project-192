
//#include "lightStructs.hlsl"

struct DirectionalLight
{
	float3 direction		: POSITION;
	float4 color			: COLOR;
};

struct VertexShaderInput
{
	float3 position			: POSITION;
	float2 uv				: TEXCOORD0;
	float3 normal			: NORMAL0;
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

float4 FragmentFunction( VertexToFragment input ) : SV_TARGET
{
	float4 texDiffuse = shaderTexture.Sample( sampleType, input.uv );

	float ndotl = saturate( dot( input.normal, -input.light.direction ) );

	float4 color = input.light.color * ndotl;
	color = color * texDiffuse;

	return float4( color.xyz, 1.0 );
}