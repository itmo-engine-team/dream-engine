Texture2D txDiffuse : register(t0);        // Буфер текстуры
SamplerState samLinear : register(s0);     // Буфер образца

cbuffer CBuf : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
};

cbuffer LightBuffer : register(b1)
{
	float4 ambientColor;
	float4 diffuseColor;
	float3 lightDirection;
	float specularPower;
	float4 specularColor;
};

cbuffer CameraBuffer : register(b2)
{
	float3 cameraPosition;
	float cameraPadding;
};

struct VS_DATA
{
	float3 pos : POSITION;
	float4 color : COLOR;
	float3 normal : NORMAL;
	float2 tex : TEXCOORD;
};

struct PS_DATA
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float3 normal : NORMAL;
	float2 tex : TEXCOORD;
	float3 viewDirection : TEXCOORD1;
};

PS_DATA VSMain(VS_DATA input)
{
	PS_DATA output;
	
	output.pos = mul(float4(input.pos, 1.0f), World);
	output.pos = mul(output.pos, View);
	output.pos = mul(output.pos, Projection);
	
	output.color = input.color;
	output.tex = input.tex;

	// Calculate the normal vector against the world matrix only.
	output.normal = mul(float4(input.normal, 0.0f), World);
	output.normal = normalize(output.normal);

	// Calculate the position of the vertex in the world.
	float4 worldPosition = mul(float4(input.pos, 1.0f), World);

	// Determine the viewing direction based on the position of the camera and the position of the vertex in the world.
	output.viewDirection = cameraPosition.xyz - worldPosition.xyz;
	output.viewDirection = normalize(output.viewDirection);

	return output;
}

float4 PSMain(PS_DATA input) : SV_Target
{
	float4 textureColor = txDiffuse.Sample(samLinear, input.tex);

    return textureColor;
}