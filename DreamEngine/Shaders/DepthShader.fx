cbuffer CBuf : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
    matrix lightView;
    matrix lightProjection;
};

struct VS_DATA
{
    float3 pos : POSITION;
};

struct PS_DATA
{
    float4 pos : SV_POSITION;
    float4 depthPos : TEXTURE0;
};

PS_DATA VSMain(VS_DATA input)
{
    PS_DATA output;

    output.pos = mul(float4(input.pos, 1.0f), World);// model, а не world
    output.pos = mul(output.pos, lightView);
    output.pos = mul(output.pos, lightProjection);
    
    output.depthPos = output.pos;

    return output;
   
}

float4 PSMain(PS_DATA input) : SV_Target
{

	// Get the depth value of the pixel by dividing the Z pixel depth by the homogeneous W coordinate.
    float depthValue = input.depthPos.z / input.depthPos.w;

    float4 finalColor;
	// First 10% of the depth buffer color red.
    if (depthValue < 0.9f)
    {
        finalColor = float4(1.0, 0.0f, 0.0f, 1.0f);
    }

	// The next 0.025% portion of the depth buffer color green.
    if (depthValue > 0.9f)
    {
        finalColor = float4(0.0, 1.0f, 0.0f, 1.0f);
    }

	// The remainder of the depth buffer color blue.
    if (depthValue > 0.925f)
    {
        finalColor = float4(0.0, 0.0f, 1.0f, 1.0f);
    }

    return finalColor;
}