cbuffer CBuf : register(b0)
{
    matrix World;
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

    /*output.pos = mul(float4(input.pos, 1.0f), World);// model, а не world
    output.pos = mul(output.pos, lightView);
    output.pos = mul(output.pos, lightProjection);
    
    output.pos.x = output.pos.x / output.pos.w - 0.15f;
    output.pos.y = output.pos.y / output.pos.w + 0.8f;
    
    output.depthPos = output.pos;*/
    
    output.pos = mul(float4(input.pos, 1.0f), World); 
    output.depthPos = output.pos;
    
    return output;
   
}

float4 PSMain(PS_DATA input) : SV_Target
{

	// Get the depth value of the pixel by dividing the Z pixel depth by the homogeneous W coordinate.
    float depthValue = input.depthPos.z / input.depthPos.w;
    return float4(depthValue, depthValue, depthValue, 1.0f);
    
}