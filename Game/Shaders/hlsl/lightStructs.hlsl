struct AmbientLight
{
	float4 color			: COLOR0;
};

struct DirectionalLight
{
	float4 color			: COLOR1;
	float3 direction		: POSITION;
};

struct PointLight
{
	float4 color			: COLOR2;
	// float 4 for proper buffering with openGL
	float3 position			: POSITION;
	float1 fallOffRadius	: PSIZE; // not sure what this should be

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

