Texture2D depthMapTexture : register(t1);
SamplerState SampleTypeClamp : register(s1);

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
	float cameraPadding;
};

struct VS_DATA
{
	float3 pos : POSITION;
	float4 color : COLOR;
	float3 normal : NORMAL;
};

struct PS_DATA
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float3 normal : NORMAL;
    float4 worldPosition : POSITION;
	float3 viewDirection : TEXCOORD0;
    float4 lightViewPosition : TEXCOORD1;
    float3 lightPos : TEXCOORD2;
};

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
    float4 textureColor = input.color;

    float bias = 0.1f;

    float2 projectTexCoord;
    projectTexCoord.x = input.lightViewPosition.x / input.lightViewPosition.w / 2.0f + 0.5f;
    projectTexCoord.y = input.lightViewPosition.y / input.lightViewPosition.w / 2.0f + 0.5f;

    float4 finalColor = ambientColor;
    float4 specular = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float3 lightDir = -lightDirection;

    if ((saturate(projectTexCoord.x) == projectTexCoord.x)
        && (saturate(projectTexCoord.y) == projectTexCoord.y))
    {
        float depthValue = depthMapTexture.Sample(SampleTypeClamp, float2(projectTexCoord.x, 1.0f - projectTexCoord.y)).r;
        // Calculate the depth of the light.
        float lightDepthValue = input.lightViewPosition.z / input.lightViewPosition.w;

        lightDepthValue = lightDepthValue - bias;

       if (lightDepthValue <= depthValue)
        {
            float lightIntensity = saturate(dot(input.normal, lightDir));
            if (lightIntensity > 0.0f)
            {
                // Determine the final diffuse color based on the diffuse color and the amount of light intensity.
                finalColor += (diffuseColor * lightIntensity);
                // Saturate the ambient and diffuse color.
                finalColor = saturate(finalColor);
            }
        }
    }

    finalColor = finalColor * textureColor;
    
    return finalColor;
}