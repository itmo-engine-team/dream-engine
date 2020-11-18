// Deferred rendering
Texture2D txColor : register(t0);
Texture2D txNormal : register(t1);

SamplerState samLinear : register(s0);     // ֱףפונ מבנאחצא

cbuffer CBuf : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
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
};

// Deferref
struct PS_Deferred
{
	float4 color : SV_Target0;
	float4 normal : SV_Target1;
};

PS_DATA VSMain(VS_DATA input)
{
	PS_DATA output;
	
	 // Calculate the position of the vertex against the world, view, and projection matrices.
	output.pos = mul(float4(input.pos, 1.0f), World);
	output.pos = mul(output.pos, View);
	output.pos = mul(output.pos, Projection);
	
	output.color = input.color;
	output.tex = input.tex;

	 // Calculate the normal vector against the world matrix only.
	output.normal = mul(input.normal, (float3x3) World);
	output.normal = normalize(output.normal);

	return output;
}

PS_Deferred PSMain(PS_DATA input) : SV_Target
{
	// Sample the colors from the color render texture using the point sampler at this texture coordinate location.
	float4 textureColor = txColor.Sample(samLinear, input.tex);

	//For Defered
	PS_Deferred output;
	output.color = textureColor;
	output.normal = float4(input.normal, 1.0f);
	
	return output;
}