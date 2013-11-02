struct VertexToFragment
{
	float4 position			: SV_POSITION;
	float2 uv				: TEXCOORD0;
	float3 normal			: NORMAL;

};

Texture2D shaderTexture;
SamplerState sampleType;

float4 main( VertexToFragment input ) : SV_TARGET
{
	return shaderTexture.Sample( sampleType, input.uv );
	//return float4( 1.0f, 0.0f, 0.0f, 1.0f );
}