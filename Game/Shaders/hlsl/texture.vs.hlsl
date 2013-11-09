
cbuffer uniforms : register( b0 )
{
	float4x4 modelViewProj;
	float4x4 modelMatrix;
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
};


VertexToFragment main( VertexShaderInput input )
{
	VertexToFragment output;

	/*matrix <float, 4, 4> testMat = { 1.35799515, 0.0, 0.0, 0.0,
									 0.0, 2.41421342, 0.0, 0.0,
									 0.0, 0.0, 1.00000095, 1.0,
									 0.0, 0.0, 2.99900293, 3.0 };*/

	//output.position = float4(input.position,1.0f);
	//output.position = mul( transpose(testMat), float4( input.position, 1.0f ) );
	output.position = mul( modelViewProj, float4( input.position, 1.0f ) );

	output.uv = input.uv;

	output.normal = normalize( mul( transpose( modelMatrix ), float4( input.normal, 1.0f ) ) ).xyz;
	
	return output;
}
