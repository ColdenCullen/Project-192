struct AmbientLight
{
	float4 color			: COLOR0;
};

struct DirectionalLight
{
	float4 color			: COLOR1;
	float4 direction		: POSITION;
};

struct PointLight
{
	float4 color			: COLOR2;
	// float 4 for proper buffering with openGL
	float4 position			: POSITION;
	// attenuation.x is constant attentuation
	// attenuation.y is linear attenuation
	// attenuation.z is quadratic attenuation
	// attenuation.w is the range of the light
	float4 attenuation		: POSITION1;

};

struct SpotLight
{
	float4 color;
	float4 position;
	float4 direction;
	float4 attenuation;
	float innerAngle;
	float outerAngle;
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

