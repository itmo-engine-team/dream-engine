Texture2D colorTexture : register(t0);
Texture2D normalTexture : register(t1);

SamplerState SampleTypePoint : register(s0);

cbuffer MatrixBuffer : register(b0)
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

cbuffer LightBuffer : register(b1)
{
    float4 ambientColor;
    float4 diffuseColor;
    float3 lightDirection;
    float specularPower;
    float4 specularColor;
};

struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};

PixelInputType VSMain(VertexInputType input)
{
    PixelInputType output;

    // Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;

    // Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);

    // Store the texture coordinates for the pixel shader.
    output.tex = input.tex;

    return output;
}

float4 PSMain(PixelInputType input) : SV_TARGET
{
    // Sample the colors from the color render texture using the point sampler at this texture coordinate location.
    float4 colors = colorTexture.Sample(SampleTypePoint, input.tex);

    // Sample the normals from the normal render texture using the point sampler at this texture coordinate location.
    float4 normals = normalTexture.Sample(SampleTypePoint, input.tex);

    // Invert the light direction for calculations.
    float3 lightDir = -lightDirection;

    // Calculate the amount of light on this pixel.
    float lightIntensity = saturate(dot(normals.xyz, lightDir));

    // Determine the final amount of diffuse color based on the color of the pixel combined with the light intensity.
    float4 outputColor = saturate(colors * lightIntensity);

    return outputColor;
}

