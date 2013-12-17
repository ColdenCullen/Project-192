#include "lightStructs.hlsl"

cbuffer uniforms //: register( b0 )
{
	matrix modelViewProj;
	matrix rotationMatrix;
	AmbientLight ambientLight;
	DirectionalLight dirLight;
};

VertexToFragment main( VertexShaderInput input )
{
	VertexToFragment output;

	output.position = mul( modelViewProj, float4( input.position, 1.0f ) );
	output.uv = input.uv;

	output.normal = normalize( mul( rotationMatrix, float4( input.normal, 1.0f ) ) ).xyz;

	output.ambientLight = ambientLight;

	output.dirLight.color = dirLight.color;//float4( 1.0, 1.0, 1.0, 1.0 );
	output.dirLight.direction = dirLight.direction;//float3( -1.0, -1.0, 1.0 );

	return output;
}
