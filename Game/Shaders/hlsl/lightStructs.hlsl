struct AmbientLight
{
	float4 color			: COLOR0;
};

struct DirectionalLight
{
	float3 direction		: POSITION;
	float4 color			: COLOR1;
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
	AmbientLight ambientLight;
	DirectionalLight dirLight;
};

