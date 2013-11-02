
#include "lightStructs.hlsl"

Texture2D shaderTexture;
SamplerState sampleType;

float4 main( VertexToFragment input ) : SV_TARGET
{
	float4 texDiffuse = shaderTexture.Sample( sampleType, input.uv );

	float ndotl = saturate( dot( input.normal, -input.light.direction ) );

	float4 color = input.light.color * ndotl;
	color = color * texDiffuse;

	return float4( color.xyz, 1.0 );
}