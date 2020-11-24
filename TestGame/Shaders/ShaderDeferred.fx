// Deferred rendering
Texture2D txColor : register(t0);
Texture2D txNormal : register(t1);

SamplerState samLinear : register(s0);

// VS Constant Buffers

cbuffer CBuf : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
};

cbuffer CameraBuffer : register(b2)
{
    float3 cameraPosition;
};

// PS Constant Buffers

cbuffer LightBuffer : register(b1)
{
    float4 ambientColor;
    float4 diffuseColor;
    float3 lightDirection;
    float specularPower;
    float4 specularColor;
};

cbuffer ModelDataBuffer : register(b3)
{
    float HasTexture;
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
    //float4 lightViewPosition : TEXCOORD2;
};

// Render targets
struct PS_Deferred
{
    float4 color : SV_Target0;
    float4 normal : SV_Target1;
    float4 specular : SV_Target2;
};

PS_DATA VSMain(VS_DATA input)
{
    PS_DATA output;

    // Calculate the position of the vertex against the world, view, and projection matrices.
    output.pos = mul(float4(input.pos, 1.0f), World);
    output.pos = mul(output.pos, View);
    output.pos = mul(output.pos, Projection);

    /*output.lightViewPosition = mul(float4(input.pos, 1.0f), World);
    output.lightViewPosition = mul(output.lightViewPosition, lightView);
    output.lightViewPosition = mul(output.lightViewPosition, lightProjection);*/

    output.color = input.color;
    output.tex = input.tex;

    // Calculate the normal vector against the world matrix only.
    output.normal = mul(input.normal, (float3x3) World);
    output.normal = normalize(output.normal);

    // Calculate the position of the vertex in the world.
    float4 worldPosition = mul(float4(input.pos, 1.0f), World);

    // Determine the viewing direction based on the position of the camera and the position of the vertex in the world.
    output.viewDirection = cameraPosition.xyz - worldPosition.xyz;
    output.viewDirection = normalize(output.viewDirection);

    return output;
}

PS_Deferred PSMain(PS_DATA input) : SV_Target
{
    // Sample the colors from the color render texture using the point sampler at this texture coordinate location.
    float4 textureColor = HasTexture > 0.0f ? txColor.Sample(samLinear, input.tex) : input.color;

    // Fill render targets
    PS_Deferred output;
    output.color = textureColor;
    output.normal = float4(input.normal, 1.0f);

    output.specular = float4(input.viewDirection, specularPower);

    return output;
}