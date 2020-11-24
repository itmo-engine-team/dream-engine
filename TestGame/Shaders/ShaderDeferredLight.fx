Texture2D colorTexture : register(t0);
Texture2D normalTexture : register(t1);
Texture2D specularTexture : register(t2);
Texture2D lightViewPosTexture : register(t3);

Texture2D depthMapTexture : register(t4);

SamplerState deferredSampler : register(s0);
SamplerState depthMapSampler : register(s1);

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

struct DeferredData
{
    float4 color;
    float3 normal;
    float3 viewDirection;
    float4 lightViewPos;
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

float4 PSCalculateLightColor(DeferredData deferredData)
{
    float4 lightColor = ambientColor;
    float4 specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

    float3 lightDir = -lightDirection;
    float lightIntensity = saturate(dot(deferredData.normal, lightDir));
    if (lightIntensity > 0.0f)
    {
        // Diffuse light
        lightColor += (diffuseColor * lightIntensity);
        lightColor = saturate(lightColor);

        // Specular light
        float3 reflection = normalize(2 * lightIntensity * deferredData.normal - lightDir);
        specular = pow(saturate(dot(reflection, deferredData.viewDirection)), specularPower);
    }

    lightColor *= deferredData.color;
    lightColor = saturate(lightColor + specular);

    return lightColor;
}

float4 PSCalculateLightColorWithShadow(DeferredData deferredData)
{
    float4 lightColor = ambientColor * deferredData.color;

    float2 projectTexCoord;
    projectTexCoord.x = deferredData.lightViewPos.x / deferredData.lightViewPos.w / 2.0f + 0.5f;
    projectTexCoord.y = deferredData.lightViewPos.y / deferredData.lightViewPos.w / 2.0f + 0.5f;

    if ((saturate(projectTexCoord.x) == projectTexCoord.x)
        && (saturate(projectTexCoord.y) == projectTexCoord.y))
    {
        float depthValue = depthMapTexture.Sample(depthMapSampler,
            float2(projectTexCoord.x, 1.0f - projectTexCoord.y)
        ).r;
        float lightDepthValue = deferredData.lightViewPos.z / deferredData.lightViewPos.w;

        float bias = 0.001f;
        lightDepthValue = lightDepthValue - bias;

        if (lightDepthValue <= depthValue)
        {
            lightColor = PSCalculateLightColor(deferredData);
        }
    }

    return lightColor;
}

float4 PSMain(PixelInputType input) : SV_TARGET
{
    DeferredData deferredData;
    deferredData.color = colorTexture.Sample(deferredSampler, input.tex);
    deferredData.normal = normalTexture.Sample(deferredSampler, input.tex).xyz;
    deferredData.viewDirection = specularTexture.Sample(deferredSampler, input.tex).xyz;
    deferredData.lightViewPos = lightViewPosTexture.Sample(deferredSampler, input.tex);

    return PSCalculateLightColorWithShadow(deferredData);
}

