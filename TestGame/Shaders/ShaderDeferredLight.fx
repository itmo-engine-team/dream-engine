Texture2D colorTexture : register(t0);
Texture2D normalTexture : register(t1);
Texture2D specularTexture : register(t2);

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

float4 PSCalculateLightColor(float4 color, float3 normal, float3 viewDirection)
{
    float4 lightColor = ambientColor;
    float4 specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

    float3 lightDir = -lightDirection;
    float lightIntensity = saturate(dot(normal, lightDir));
    if (lightIntensity > 0.0f)
    {
        // Diffuse light
        lightColor += (diffuseColor * lightIntensity);
        lightColor = saturate(lightColor);

        // Specular light
        float3 reflection = normalize(2 * lightIntensity * normal - lightDir);
        specular = pow(saturate(dot(reflection, viewDirection)), specularPower);
    }

    lightColor *= color;
    lightColor = saturate(lightColor + specular);

    return lightColor;
}

float4 PSMain(PixelInputType input) : SV_TARGET
{
    float4 colors = colorTexture.Sample(SampleTypePoint, input.tex);
    float4 normals = normalTexture.Sample(SampleTypePoint, input.tex);
    float4 speculars = specularTexture.Sample(SampleTypePoint, input.tex);

    return PSCalculateLightColor(colors, normals.xyz, speculars.xyz);
}

