
//#include "lightStructs.h"

struct DirectionalLight
{
	float3 direction		: POSITION;
	float4 color			: COLOR;
};

struct VertexShaderInput
{
	float3 position			: POSITION;
	float2 uv				: TEXCOORD0;
	float3 normal			: NORMAL;
};

struct VertexToFragment
{
	float4 position			: SV_POSITION;
	float2 uv				: TEXCOORD0;
	float3 normal			: NORMAL;
	DirectionalLight light;
};


cbuffer uniforms : register( b0 )
{
	matrix modelViewProj;
	matrix modelMatrix;
};

VertexToFragment main( VertexShaderInput input )
{
	VertexToFragment output;

	output.position = mul( modelViewProj, float4( input.position, 1.0f ) );
	output.uv = input.uv;

	output.normal = normalize( mul( transpose( modelMatrix ), float4( input.normal, 1.0f ) ) ).xyz;
	output.light.color = float4( 1.0, 1.0, 1.0, 1.0 );
	output.light.direction = float3( -1.0, -1.0, -1.0 );

	return output;
}
