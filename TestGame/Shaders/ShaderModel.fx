Texture2D txDiffuse : register(t0);       
SamplerState samLinear : register(s0);     

Texture2D depthMapTexture : register(t1); 
SamplerState depthMapSampler : register(s1); 

// VS Constant Buffers

cbuffer CBuf : register(b0)
{
    matrix World;
    matrix View;
	matrix Projection;	
    matrix lightView;
    matrix lightProjection;
};

cbuffer LightBuffer : register(b1)
{
    float4 ambientColor;
    float4 diffuseColor;
    float3 lightDirection;
    float specularPower;
    float4 specularColor;
    float lightPadding;
};

cbuffer CameraBuffer : register(b2)
{
    float3 cameraPosition;
};

// PS Constant Buffers

cbuffer ModelDataBuffer : register(b3)
{
    float HasTexture;
    float HasLight;
    float HasShadow;
};

// Input Data

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
    float4 lightViewPosition : TEXCOORD2;
};

// Vertex Shader

PS_DATA VSMain(VS_DATA input)
{
    PS_DATA output;
	
    output.pos = mul(float4(input.pos, 1.0f), World);
    output.pos = mul(output.pos, View);
    output.pos = mul(output.pos, Projection);
	
    output.lightViewPosition = mul(float4(input.pos, 1.0f), World);
    output.lightViewPosition = mul(output.lightViewPosition, lightView);
    output.lightViewPosition = mul(output.lightViewPosition, lightProjection);
	
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

// Pixel Shader

float4 PSCalculateLightColor(PS_DATA input, float4 textureColor)
{
    float4 lightColor = ambientColor;
    float4 specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

    float3 lightDir = -lightDirection;
    float lightIntensity = saturate(dot(input.normal, lightDir));
    if (lightIntensity > 0.0f)
    {
        // Diffuse light
        lightColor += (diffuseColor * lightIntensity);
        lightColor = saturate(lightColor);

        // Specular light
        float3 reflection = normalize(2 * lightIntensity * input.normal - lightDir);
        specular = pow(saturate(dot(reflection, input.viewDirection)), specularPower);
    }

    lightColor *= textureColor;
    lightColor = saturate(lightColor + specular);

    return lightColor;
}

float4 PSCalculateLightColorWithShadow(PS_DATA input, float4 textureColor)
{
    float4 lightColor = ambientColor * textureColor;

    float2 projectTexCoord;
    projectTexCoord.x = input.lightViewPosition.x / input.lightViewPosition.w / 2.0f + 0.5f;
    projectTexCoord.y = input.lightViewPosition.y / input.lightViewPosition.w / 2.0f + 0.5f;

    if ((saturate(projectTexCoord.x) == projectTexCoord.x)
        && (saturate(projectTexCoord.y) == projectTexCoord.y))
    {
        float depthValue = depthMapTexture.Sample(depthMapSampler, float2(projectTexCoord.x, 1.0f - projectTexCoord.y)).r;
        float lightDepthValue = input.lightViewPosition.z / input.lightViewPosition.w;

        float bias = 0.001f;
        lightDepthValue = lightDepthValue - bias;

        if (lightDepthValue <= depthValue)
        {
            lightColor = PSCalculateLightColor(input, textureColor);
        }
    }

    return lightColor;
}

float4 PSMain(PS_DATA input) : SV_Target
{
    float4 textureColor = HasTexture > 0.0f ? txDiffuse.Sample(samLinear, input.tex) : input.color;

    if (HasLight > 0.0f)
    {
        float4 finalColor = HasShadow > 0.0f
            ? PSCalculateLightColorWithShadow(input, textureColor)
            : PSCalculateLightColor(input, textureColor);

        return finalColor;
    }
    
    return textureColor;
}